#include <bits/stdc++.h>

using namespace std;

const string surrounded = "surrounded";
const string floating = "floating";
const string embedded = "embedded";

const string LAYOUT = "layout";
const string WIDTH = "width";
const string HEIGHT = "height";
const string DX = "dx";
const string DY = "dy";

struct Param {
    string name;
    string value;
    Param() {}
    Param(string name, string value) {
        this->name = std::move(name);
        this->value = std::move(value);
    }
};

Param strToParam(const string& paramStr) {
    string delimiter = "=";
    int delimiterPos = paramStr.find(delimiter);
    string paramName = paramStr.substr(0, delimiterPos);
    string paramValue = paramStr.substr(delimiterPos + delimiter.size());
    return {paramName, paramValue};
}

struct Image {
    string layout;
    int width, height, dx = -1, dy = -1;
    explicit Image(const vector<string>& imageParams) {
        Param param;
        for (const string& paramStr: imageParams) {
            param = strToParam(paramStr);
            if (param.name == LAYOUT) layout = param.value;
            else if (param.name == WIDTH) width = stoi(param.value);
            else if (param.name == HEIGHT) height = stoi(param.value);
            else if (param.name == DX) dx = stoi(param.value);
            else if (param.name == DY) dy = stoi(param.value);
            else {
                cout << "WRONG PARAM PARSING";
                exit(-1);
            }
        }
    }
};

struct Line;

struct Fragment {
    int start;
    int width;
    int end;
    int leftSize;
    int index;
    Line* line;
    Fragment() {}
    Fragment(int start, int width, Line* line, int index = 0) {
        this->start = start;
        this->width = width;
        this->index = index;
        this->line = line;
        leftSize = width;
        end = start + width;
    }
    Fragment (const Fragment& fragment) {
        start = fragment.start;
        width = fragment.width;
        end = fragment.end;
        leftSize = fragment.leftSize;
        index = fragment.index;
        line = fragment.line;
    }
    bool add(int elementWidth) {
        if (leftSize < elementWidth) {
            return false;
        }
        leftSize -= elementWidth;
        return true;
    }
    bool isPointInFragment(int point) const {
        return point >= start && point < end;
    }
    bool decreaseWidthFromRight(int value) { // |123| -> |12|
        width -= end - value;
        leftSize -= end - value;
        end = value;
        return width <= 0;
    }
    bool isEmpty() const {
        return leftSize == width;
    }
    Fragment* next() const;
    friend ostream& operator<<(ostream &os, const Fragment &fragment){
        return os << "[" << fragment.start << ", " << fragment.end << "]";
    }
};

struct Line {
    int width;
    int initHeight;
    int height;
    int index;
    vector<Fragment*> fragments;
    Line(int documentWidth, int lineHeight, int index = 0) {
        height = lineHeight;
        initHeight = lineHeight;
        width = documentWidth;
        this->index = index;
        fragments = { new Fragment(0, documentWidth, this, 0)};
    }
    Line(const Line& line){
        height = line.height;
        initHeight = line.initHeight;
        width = line.width;
        index = line.index;
        fragments = line.fragments;
        for (Fragment* fragment : fragments) {
            fragment->line = this;
        }
    }
    void splitIntoFragments(int fragmentSplitterStart, int fragmentSplitterEnd) {
        int i = 0;
        int fragmentToDeletePos = -1;
        for (Fragment* fragment : fragments) {
            ++i;
            if (fragment->isPointInFragment(fragmentSplitterStart)) {
                int fragmentEnd = fragment->end;
                if (fragment->decreaseWidthFromRight(fragmentSplitterStart)) {
                    fragmentToDeletePos = i - 1;
                }
                if (fragmentSplitterEnd != fragmentEnd) {
                    fragments.insert(fragments.begin() + i,
                            new Fragment(
                                    fragmentSplitterEnd,
                                    fragmentEnd - fragmentSplitterEnd,
                                    this,
                                    i
                                )
                            );
                }
                break;
            }
        }
        if (fragmentToDeletePos != -1) {
            fragments.erase(fragments.begin() + fragmentToDeletePos);
        }
        i = 0;
        for (Fragment* fragment : fragments) {
            fragment->index = i++;
        }
    }
    void print() const {
        for (Fragment* fragment : fragments) {
            cout << &fragment << " ";
        }
        cout << endl;
    }
};

vector<Line> lines;

Fragment* activeFragment;

int totalLinesHeight = 0;

struct Splitter {
    int start;
    int end;
    int absoluteBottom;
    Splitter(int start, int end, int absoluteBottom) {
        this->start = start;
        this->end = end;
        this->absoluteBottom = absoluteBottom;
    }
};

vector<Splitter*> activeSplitters;

void addLine(int width, int height) {
    lines.emplace_back(width, height, lines.size());
    vector<Splitter*> splittersToDelete;
    for (Splitter* splitter: activeSplitters) {
        if (splitter->absoluteBottom <= totalLinesHeight) {
            splittersToDelete.emplace_back(splitter);
            continue;
        }
        lines.back().splitIntoFragments(splitter->start, splitter->end);
    }
    totalLinesHeight += height;
    for (Splitter* splitter: splittersToDelete) {
        remove(activeSplitters.begin(), activeSplitters.end(), splitter);
    }
    splittersToDelete.clear();
}

Fragment* Fragment::next() const {
    Line* fragmentLine = line;
    if (index == line->fragments.size() - 1) {
        if (fragmentLine->index == lines.size() - 1) {
            addLine(fragmentLine->width, fragmentLine->initHeight);
            return lines.back().fragments.front();
        }
        else {
            return lines[fragmentLine->index + 1].fragments.front();
        }
    }
    else {
        return fragmentLine->fragments[index + 1];
    }
}

void AddToFirstSuitableFragment(int width, int height = 0, int spaceWidth = 0) {
    bool spaceRemoved = false;
    while (true) {
        if (activeFragment->add(width)) {
            if (activeFragment->line->height < height) {
                totalLinesHeight += height - activeFragment->line->height;
                activeFragment->line->height = height;
            }
            break;
        }
        if (!spaceRemoved) {
            spaceRemoved = true;
            width -= spaceWidth;
        }
        activeFragment = activeFragment->next();
    }
}

pair<int, int> getActiveFragmentsTopLeftCornerOfFreeSpace() {
    Line& fragmentLine = *activeFragment->line;
    int height = totalLinesHeight - fragmentLine.height;
    int width = activeFragment->start + activeFragment->width - activeFragment->leftSize;
    return {width, height};
}

void solve() {
    int documentWidth, lineHeight, charWidth;

    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Error opening the file" << std::endl;
    }

    inputFile >> documentWidth >> lineHeight >> charWidth;

    addLine(documentWidth, lineHeight);
    activeFragment = lines.front().fragments.front();

    bool needSpace = false;

    bool lastIsFloating = false;
    pair<int, int> lastFloatingTopRight;

    string line;
    getline(inputFile, line);
    while (getline(inputFile, line)) {
        if (line.empty()) {//if empty line
                addLine(documentWidth, lineHeight);
            activeFragment = lines.back().fragments.front();
            needSpace = false;
            lastIsFloating = false;
        }
        else {
            istringstream iss(line);
            string word;
            while (iss >> word) {
                // if image
                if (word.starts_with('(')) {
                    vector<string> imageParams;
                    bool read = true;
                    while (read) {
                        while (!(iss >> word)) {
                            getline(inputFile, line);
                            iss = istringstream(line);
                        }
                        if (word.ends_with(')')) {
                            word = word.substr(0, word.size() - 1);
                            read = false;
                        }
                        imageParams.emplace_back(word);
                    }
                    Image image(imageParams);

                    if (image.layout == surrounded) {
                        AddToFirstSuitableFragment(image.width);
                        pair<int, int> coords = getActiveFragmentsTopLeftCornerOfFreeSpace();
                        cout << coords.first - image.width << " " << coords.second << endl;

                        if (coords.second + image.height > totalLinesHeight) {
                        activeSplitters.push_back(new Splitter(
                                coords.first - image.width,
                                coords.first,
                                coords.second + image.height
                                ));
                        }
                        needSpace = false;
                        lastIsFloating = false;
                    }
                    else if (image.layout == embedded) {
                        int width = image.width + charWidth * needSpace * !activeFragment->isEmpty();
                        AddToFirstSuitableFragment(width, image.height, charWidth * needSpace * !activeFragment->isEmpty());
                        pair<int, int> coords = getActiveFragmentsTopLeftCornerOfFreeSpace();
                        cout << coords.first - image.width << " " << coords.second << endl;
                        needSpace = true;
                        lastIsFloating = false;
                    }
                    else if (image.layout == floating) {
                        pair<int, int> coords;
                        if (lastIsFloating) {
                            coords = lastFloatingTopRight;
                        }
                        else {
                            coords = getActiveFragmentsTopLeftCornerOfFreeSpace();
                        }
                        int xCoord = coords.first + image.dx;

                        if (xCoord + image.width > documentWidth) {
                            xCoord = documentWidth - image.width;
                        }
                        xCoord = max(0, xCoord);
                        cout << xCoord << " ";
                        cout << coords.second + image.dy << endl;
                        lastIsFloating = true;
                        lastFloatingTopRight.first = xCoord + image.width;
                        lastFloatingTopRight.second = coords.second + image.dy;
                    }
                    else {
                        cout << "WRONG LAYOUT";
                        exit(-1);
                    }
                }
                else {// if word
                    int wordLength = word.size() + needSpace * !activeFragment->isEmpty();
                    int width = wordLength * charWidth;
                    AddToFirstSuitableFragment(width, 0, charWidth * needSpace * !activeFragment->isEmpty());
                    pair<int, int> coords = getActiveFragmentsTopLeftCornerOfFreeSpace();
                    needSpace = true;
                    lastIsFloating = false;
                }
            }
        }
    }
    inputFile.close();
}

int main() {
    solve();
    return 0;
}
