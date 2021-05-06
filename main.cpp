#include <iostream>
#include <tuple>
#include <chrono>
#include <vector>
#include <memory>

    

using namespace std;

using namespace std::chrono_literals;

const int TIMEOUT = 400; // maximum number of milliseconds that a player is allowed to take

class Position {
public:
std::tuple<int, int> pos;
// TODO Implement the operator == and other operators if necessary

Position(tuple<int, int> &pos) {
    this->pos = pos;
}

Position() {

}


bool operator==(Position &obj) {
    if (obj.pos == this->pos) {
        return true;
    }
    return false;
}

bool operator!=(Position &obj) {
    if (obj.pos == this->pos) {
        return false;
    }
    return true;
}


tuple<int, int> &getPos() {
    return pos;
}

int &getPos0() {
    return get<0>(pos);
}

int &getPos1() {
    return get<1>(pos);
}
};

class Item {
public:
char unitType;

bool capitalCase;

bool isEmpty = true;

Position position;

string className;

Item(char &unitType, Position position) {
    this->unitType = unitType;
    this->position = position;
    this->isEmpty = false;
    if (unitType == 'r' || unitType == 'p' || unitType == 's' || unitType == 'f')
        capitalCase = false;
    else
        capitalCase = true;

}

bool operator==(Item &obj) {
    if (this->unitType == obj.unitType && this->position == obj.position) {
        return true;
    }
    return false;
}

Item() {
    isEmpty = true;
}

Item(bool isEmpty) {
    this->isEmpty = true;

}

char getUnitType() const {
    return unitType;
}

bool isCapitalCase() const {
    return capitalCase;
}

const Position &getPosition() const {
    return position;
}
};

class Rock : public Item {
public:
Rock() : Item() {}

Rock(char &unitType, Position &position) : Item(unitType, position) {
    this->className = "rock";
}
};

class Paper : public Item {
public:
Paper() : Item() {
}

Paper(char &unitType, Position &position) : Item(unitType, position) {
    this->className = "paper";
}
};

class Scissors : public Item {
public:
Scissors() : Item() {}

Scissors(char &unitType, Position &position) : Item(unitType, position) {
    this->className = "scissors";
}
};

class Flag : public Item {
public:
Flag() : Item() {}

Flag(char &unitType, Position &position) : Item(unitType, position) {
    this->className = "flag";
}
};

class Mountains : public Item {
public:

Mountains() : Item() {}

Mountains(char &unitType, Position &position) : Item(unitType, position) {
    this->className = "mountains";
    this->isEmpty = false;
}

Position &getPosition() {
    return position;
}
};

template<class T>

class Portal : public Item {

public:
Portal() {

}

Portal(T &unitType, const Position &position) : Item(unitType, position) {
    this->isEmpty = true;
    this->className = "portal";
}
};

class Action {
public:
Action() {

}

Position from; // current row, column of the unit to be moved
Position to; // position to where the unit must be moved


Action(Position &from, Position &to) {
    this->from = from;
    this->to = to;
}

Position &getTo() {
    return to;
}

void setFrom(Position &from) {
    Action::from = from;
}

void setTo(Position &to) {
    Action::to = to;
}


};

class World {
// TODO Create a container of smart pointers of units and flags of player 0

// TODO Create a container of smart pointers of units and flags of player 1
// TODO Create a container of smart pointers of mountains
public:
vector<shared_ptr<Item>> player0;

vector<shared_ptr<Item>> groupOfItems;

vector<Mountains> moun;

vector<vector<shared_ptr<Item>>> world;

World() {

}

World(int n1, int n2, int n3, int n4) {

    world.resize(15);

    tuple pos = make_tuple(0, 0);

    Position pf0(pos);

    char f = 'f';

    Flag flag0(f, pf0);

    auto ptr = make_shared<Item>(flag0);

    player0.push_back(ptr);

    tuple pos1 = make_tuple(14, 14);

    Position pf1(pos1);

    char F = 'F';

    Flag flag1(F, pf1);

    auto ptr1 = make_shared<Item>(flag1);

    groupOfItems.push_back(ptr1);


    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 15; ++j) {
            Item temp(true);
            world[i].push_back(make_shared<Item>(temp));
        }


    world[0][0] = ptr;

    world[14][14] = ptr1;

    for (int i = 1; i <= 5; ++i) {

        int x = 0;

        int y = i;

        tuple pos = make_tuple(x, y);

        Position rp0(pos);

        char r = 'r';

        Rock rock0(r, rp0);

        auto ptr = make_shared<Item>(rock0);

        player0.push_back(ptr);

        world[x][y] = ptr;

        x += 3;

        tuple pos2 = make_tuple(x, y);

        Position rp02(pos2);

        Rock rock02(r, rp0);

        auto ptr2 = make_shared<Item>(rock02);

        player0.push_back(ptr2);

        world[x][y] = ptr2;
        x -= 3;
        y += 8;
        x += 14;
        pos = make_tuple(x, y);

        Position rp1(pos);

        char R = 'R';

        Rock rock1(R, rp1);

        auto ptr1 = make_shared<Item>(rock1);

        groupOfItems.push_back(ptr1);

        world[x][y] = ptr1;

        x -= 3;

        pos = make_tuple(x, y);

        Position rp13(pos);


        Rock rock13(R, rp13);

        auto ptr13 = make_shared<Item>(rock13);

        groupOfItems.push_back(ptr13);

        world[x][y] = ptr13;


    }


    for (int i = 1; i <= 5; ++i) {

        int x = 1;

        int y = i;

        if (world[x][y]->isEmpty) {

            tuple pos = make_tuple(x, y);

            Position pp0(pos);

            char p = 'p';

            Paper paper0(p, pp0);

            auto ptr = make_shared<Item>(paper0);

            player0.push_back(ptr);

            world[x][y] = ptr;

            x += 3;

            pos = make_tuple(x, y);

            Position pp2(pos);


            Paper paper2(p, pp2);

            auto ptr2 = make_shared<Item>(paper2);

            player0.push_back(ptr2);

            world[x][y] = ptr2;
            x -= 3;
            x += 12;
            y += 8;

            pos = make_tuple(x, y);

            Position pp1(pos);

            char P = 'P';

            Paper paper1(P, pp1);

            auto ptr1 = make_shared<Item>(paper1);

            groupOfItems.push_back(ptr1);

            world[x][y] = ptr1;

            x -= 3;

            pos = make_tuple(x, y);

            Position pp4(pos);


            Paper paper3(P, pp4);

            auto ptr3 = make_shared<Item>(paper3);

            groupOfItems.push_back(ptr3);

            world[x][y] = ptr3;
        }
    }

    for (int i = 1; i <= 5; ++i) {

        int x = 2;

        int y = i;

        if (world[x][y]->isEmpty) {

            tuple pos = make_tuple(x, y);

            Position sp0(pos);

            char s = 's';

            Scissors scissors(s, sp0);

            auto ptr = make_shared<Item>(scissors);

            player0.push_back(ptr);

            world[x][y] = ptr;

            x += 3;

            pos = make_tuple(x, y);

            Position sp2(pos);


            Scissors scissors2(s, sp2);

            auto ptr2 = make_shared<Item>(scissors);

            player0.push_back(ptr2);

            world[x][y] = ptr2;
            x -= 3;

            x += 10;
            y += 8;

            pos = make_tuple(x, y);

            Position sp1(pos);

            char S = 'S';

            Scissors scissors1(S, sp1);

            auto ptr1 = make_shared<Item>(scissors1);

            groupOfItems.push_back(ptr1);

            world[x][y] = ptr1;

            x -= 3;

            pos = make_tuple(x, y);

            Position sp3(pos);


            Scissors scissors3(S, sp3);

            auto ptr3 = make_shared<Item>(scissors3);

            groupOfItems.push_back(ptr3);

            world[x][y] = ptr3;
        }
    }
    createMoutains();

    char aster = '*';

    tuple<int, int> pos0 = make_tuple(1, 0);

    Position aspos0(pos0);
    Portal portal0(aster, aspos0);

    auto ptr_portal0 = make_shared<Item>(portal0);

    world[1][0] = ptr_portal0;

    tuple<int, int> pos2 = make_tuple(8, 6);

    Position aspos1(pos2);
    Portal portal1(aster, aspos1);

    auto ptr_portal1 = make_shared<Item>(portal1);

    world[8][6] = ptr_portal1;


}

void createMoutains() {
    int y = 2;
    int x = 10;

    tuple<int, int> pos = make_tuple(x, y);

    Position m(pos);

    char M = 'M';

    Mountains mountains(M, m);

    moun.push_back(mountains);

    world[x][y] = make_shared<Item>(mountains);


    x = 11;
    pos = make_tuple(x, y);

    Position m11(pos);


    Mountains mountains11(M, m11);

    moun.push_back(mountains11);

    world[x][y] = make_shared<Item>(mountains11);

    x = 12;
    pos = make_tuple(x, y);

    Position m12(pos);


    Mountains mountains12(M, m12);

    moun.push_back(mountains12);

    world[x][y] = make_shared<Item>(mountains12);


    x = 10;
    y = 4;
    pos = make_tuple(x, y);

    Position m13(pos);


    Mountains mountains13(M, m13);

    moun.push_back(mountains13);

    world[x][y] = make_shared<Item>(mountains13);


    x = 11;
    pos = make_tuple(x, y);

    Position m14(pos);


    Mountains mountains14(M, m14);

    moun.push_back(mountains14);

    world[x][y] = make_shared<Item>(mountains14);


    x = 12;
    pos = make_tuple(x, y);

    Position m15(pos);


    Mountains mountains15(M, m15);

    moun.push_back(mountains15);

    world[x][y] = make_shared<Item>(mountains15);


    x = 12;
    y = 5;
    pos = make_tuple(x, y);

    Position m16(pos);


    Mountains mountains16(M, m16);

    moun.push_back(mountains16);

    world[x][y] = make_shared<Item>(mountains16);

    x = 10;
    y = 6;
    pos = make_tuple(x, y);

    Position m17(pos);


    Mountains mountains17(M, m17);

    moun.push_back(mountains17);

    world[x][y] = make_shared<Item>(mountains17);

    x = 11;

    pos = make_tuple(x, y);

    Position m18(pos);


    Mountains mountains18(M, m18);

    moun.push_back(mountains18);

    world[x][y] = make_shared<Item>(mountains18);

    x = 12;

    pos = make_tuple(x, y);

    Position m20(pos);


    Mountains mountains20(M, m20);

    moun.push_back(mountains20);

    world[x][y] = make_shared<Item>(mountains20);


    x = 7;
    y = 6;

    pos = make_tuple(x, y);

    Position m1(pos);


    Mountains mountains1(M, m1);

    moun.push_back(mountains1);

    world[x][y] = make_shared<Item>(mountains1);

    x = 7;
    y = 7;

    pos = make_tuple(x, y);

    Position m2(pos);


    Mountains mountains2(M, m2);

    moun.push_back(mountains2);

    world[x][y] = make_shared<Item>(mountains2);

    x = 7;
    y = 8;

    pos = make_tuple(x, y);

    Position m3(pos);


    Mountains mountains3(M, m3);

    moun.push_back(mountains3);

    world[x][y] = make_shared<Item>(mountains3);

    x = 4;
    y = 9;

    pos = make_tuple(x, y);

    Position m4(pos);


    Mountains mountains4(M, m4);

    moun.push_back(mountains4);

    world[x][y] = make_shared<Item>(mountains4);


    x = 4;
    y = 13;

    pos = make_tuple(x, y);

    Position m5(pos);


    Mountains mountains5(M, m5);

    moun.push_back(mountains5);

    world[x][y] = make_shared<Item>(mountains5);

    x = 2;
    y = 10;

    pos = make_tuple(x, y);

    Position m6(pos);


    Mountains mountains6(M, m6);

    moun.push_back(mountains6);

    world[x][y] = make_shared<Item>(mountains6);

    x = 2;
    y = 12;

    pos = make_tuple(x, y);

    Position m7(pos);


    Mountains mountains7(M, m7);

    moun.push_back(mountains7);

    world[x][y] = make_shared<Item>(mountains7);

    x = 5;
    y = 10;

    pos = make_tuple(x, y);

    Position m8(pos);


    Mountains mountains8(M, m8);

    moun.push_back(mountains8);

    world[x][y] = make_shared<Item>(mountains8);

    x = 5;
    y = 11;

    pos = make_tuple(x, y);

    Position m9(pos);


    Mountains mountains9(M, m9);

    moun.push_back(mountains9);

    world[x][y] = make_shared<Item>(mountains9);


    x = 5;
    y = 12;

    pos = make_tuple(x, y);

    Position m10(pos);


    Mountains mountains10(M, m10);

    moun.push_back(mountains10);

    world[x][y] = make_shared<Item>(mountains10);

}

void printWorld() {

    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (!world[i][j]->isEmpty || world[i][j]->className == "portal")
                cout << world[i][j]->unitType << " ";
            else
                cout << "- ";

        }
        cout << endl;
    }
}

shared_ptr<Item> findByPosition(Position &pos, vector<shared_ptr<Item>> obj) {
    for (int i = 0; i < obj.size(); ++i) {
        if (obj[i]->position == pos) {
            return obj[i];
        }
    }
    return nullptr;
}

shared_ptr<Item> findByCoordinates(Position &pos) {
    return world[pos.getPos0()][pos.getPos1()];
}

void killingItem(shared_ptr<Item> item, vector<shared_ptr<Item>> &items) {


    for (auto unit = items.begin(); unit != items.end(); ++unit) {
        if (**unit == *item) {
            items.erase(unit);
            break;
        }
    }


}

void
fightInWorld(shared_ptr<Item> &person0, shared_ptr<Item> &person1, Position &fromLocation, Position &toLocation,
             vector<shared_ptr<Item>> &groupOfItems) {
    if (person1->className == "rock") {
        if (person0->className == "paper") {
            person0->position = toLocation;
            Item temp(true);

            world[fromLocation.getPos0()][fromLocation.getPos1()] = make_shared<Item>(temp);

            if (!world[toLocation.getPos0()][toLocation.getPos1()]->isEmpty) {

                killingItem(world[toLocation.getPos0()][toLocation.getPos1()], groupOfItems);
                world[toLocation.getPos0()][toLocation.getPos1()] = make_shared<Item>(temp);


            }

            world[toLocation.getPos0()][toLocation.getPos1()] = person0;
        } else if (person0->className == "scissors") {
            Item temp(true);

            killingItem(world[fromLocation.getPos0()][fromLocation.getPos1()], groupOfItems);

            world[fromLocation.getPos0()][fromLocation.getPos1()] = make_shared<Item>(temp);

        }
    } else if (person1->className == "paper") {
        if (person0->className == "scissors") {
            person0->position = toLocation;
            Item temp(true);

            world[fromLocation.getPos0()][fromLocation.getPos1()] = make_shared<Item>(temp);

            if (!world[toLocation.getPos0()][toLocation.getPos1()]->isEmpty) {
                killingItem(world[toLocation.getPos0()][toLocation.getPos1()], groupOfItems);
                world[toLocation.getPos0()][toLocation.getPos1()] = make_shared<Item>(temp);


            }

            world[toLocation.getPos0()][toLocation.getPos1()] = person0;
        } else if (person0->className == "rock") {
            Item temp(true);
            killingItem(world[fromLocation.getPos0()][fromLocation.getPos1()], groupOfItems);
            world[fromLocation.getPos0()][fromLocation.getPos1()] = make_shared<Item>(temp);

        }
    } else if (person1->className == "scissors") {
        if (person0->className == "rock") {
            person0->position = toLocation;
            Item temp(true);

            world[fromLocation.getPos0()][fromLocation.getPos1()] = make_shared<Item>(temp);

            if (!world[toLocation.getPos0()][toLocation.getPos1()]->isEmpty) {
                killingItem(world[toLocation.getPos0()][toLocation.getPos1()], groupOfItems);
                world[toLocation.getPos0()][toLocation.getPos1()] = make_shared<Item>(temp);


            }

            world[toLocation.getPos0()][toLocation.getPos1()] = person0;
        } else if (person0->className == "paper") {
            Item temp(true);
            cout << "I'm here" << endl;
            cout << person0->unitType << " " << person0->position.getPos0() << " " << person0->position.getPos1()
                 << endl;
            killingItem(world[fromLocation.getPos0()][fromLocation.getPos1()], groupOfItems);
            world[fromLocation.getPos0()][fromLocation.getPos1()] = make_shared<Item>(temp);

        }
    }

}

bool validateTheAction(Action action0, Action action1) {

    if (action0.to == action1.to) {

        shared_ptr<Item> obj0 = this->findByPosition(action0.from, this->player0);

        shared_ptr<Item> obj1 = this->findByPosition(action1.from, this->groupOfItems);

        if (obj0->className == "rock") {

            if (obj1->className == "scissors") {
                obj0->position = action0.to;

                shared_ptr<Item> item = world[action0.to.getPos0()][action0.to.getPos1()];
                killingItem(item, groupOfItems);

                world[action0.to.getPos0()][action0.to.getPos1()] = obj0;

                Item temp(true);
                world[action0.from.getPos0()][action0.from.getPos1()] = make_shared<Item>(temp);

            } else if (obj1->className == "paper") {
                obj1->position = action1.to;
                shared_ptr<Item> item = world[action1.to.getPos0()][action1.to.getPos1()];
                killingItem(item, player0);
                world[action1.to.getPos0()][action1.to.getPos1()] = obj1;
                Item temp(true);
                world[action1.from.getPos0()][action1.from.getPos1()] = make_shared<Item>(temp);

            }

        } else if (obj0->className == "scissors") {

            if (obj1->className == "paper") {

                shared_ptr<Item> item = world[action0.to.getPos0()][action0.to.getPos1()];
                killingItem(item, groupOfItems);
                obj0->position = action0.to;
                world[action0.to.getPos0()][action0.to.getPos1()] = obj0;
                Item temp(true);
                world[action0.from.getPos0()][action0.from.getPos1()] = make_shared<Item>(temp);

            } else if (obj1->className == "rock") {
                obj1->position = action1.to;
                shared_ptr<Item> item = world[action1.to.getPos0()][action1.to.getPos1()];
                killingItem(item, player0);
                world[action1.to.getPos0()][action1.to.getPos1()] = obj1;
                Item temp(true);
                world[action1.from.getPos0()][action1.from.getPos1()] = make_shared<Item>(temp);

            }

        } else if (obj0->className == "paper") {

            if (obj1->className == "rock") {

                obj0->position = action0.to;
                shared_ptr<Item> item = world[action0.to.getPos0()][action0.to.getPos1()];
                killingItem(item, groupOfItems);
                world[action0.to.getPos0()][action0.to.getPos1()] = obj0;
                Item temp(true);
                world[action0.from.getPos0()][action0.from.getPos1()] = make_shared<Item>(temp);

            } else if (obj1->className == "scissors") {
                obj1->position = action1.to;
                shared_ptr<Item> item = world[action1.to.getPos0()][action1.to.getPos1()];
                killingItem(item, player0);
                world[action1.to.getPos0()][action1.to.getPos1()] = obj1;
                Item temp(true);
                world[action1.from.getPos0()][action1.from.getPos1()] = make_shared<Item>(temp);

            }

        }


    } else {

        for (int i = 0; i < this->moun.size(); ++i) {
            if (action1.to == this->moun[i].position) {
                cout << "Fell from high ground!(PlayerOne)" << endl;
                return true;
            } else if (action0.to == this->moun[i].position) {
                cout << "Fell from high ground!(PlayerZero)" << endl;
                return true;
            }
        }

        shared_ptr<Item> move0 = findByPosition(action0.from, this->player0);

        shared_ptr<Item> move1 = findByPosition(action1.from, this->groupOfItems);

        shared_ptr<Item> t0 = findByCoordinates(action0.to);
        shared_ptr<Item> t1 = findByCoordinates(action1.to);
        if (!t0->isEmpty && t0->className != "flag") {
            fightInWorld(move0, t0, action0.from, action0.to, player0);
        } else {
            move0->position = action0.to;
            world[action0.to.getPos0()][action0.to.getPos1()] = move0;
            Item temp(true);
            world[action0.from.getPos0()][action0.from.getPos1()] = make_shared<Item>(temp);


        }
        if (!t1->isEmpty && t1->className != "flag") {
            fightInWorld(move1, t1, action1.from, action1.to, groupOfItems);
        } else {
            move1->position = action1.to;
            Item temp(true);
            world[action1.to.getPos0()][action1.to.getPos1()] = move1;
            world[action1.from.getPos0()][action1.from.getPos1()] = make_shared<Item>(temp);

        }


        if (action0.to.getPos() == make_tuple(14, 14)) {
            cout << "Zero player won!" << endl;
            return true;
        } else if (action1.to.getPos() == make_tuple(0, 0)) {
            cout << "First player won!" << endl;
            return true;
        } else { return false; }


    }

    return false;
}

};

Action actionPlayerZero(World &world) {

double minDist = 1e6;

shared_ptr<Item> movebleObj = world.player0[1];

for (int i = 1; i < world.player0.size(); i++) {

    if (28 - (world.player0[i]->position.getPos0() + world.player0[i]->position.getPos1()) <= minDist) {

        minDist = 28 - (world.player0[i]->position.getPos0() + world.player0[i]->position.getPos1());


        movebleObj = world.player0[i];
    }
}

int directionToFlag = 1;
shared_ptr<Item> temp;
shared_ptr<Item> temp1;
Action action0;
if (movebleObj->position.getPos0() + directionToFlag <= 14) {
    temp = world.world[movebleObj->position.getPos0() + directionToFlag][movebleObj->position.getPos1()];
}
if (movebleObj->position.getPos1() + directionToFlag <= 14) {
    temp1 = world.world[movebleObj->position.getPos0()][movebleObj->position.getPos1() + directionToFlag];
}


if (movebleObj->position.getPos1() + directionToFlag <= 14 &&
    (temp1->isEmpty || (movebleObj->capitalCase != temp1->capitalCase)) && temp1->className != "mountains") {


    int x = movebleObj->position.getPos1() + directionToFlag;

    tuple<int, int> pos = make_tuple(movebleObj->position.getPos0(), x);

    Position *to = new Position(pos);

    Position *from = new Position(movebleObj->position);
    action0.setFrom(*from);
    action0.setTo(*to);

} else if (movebleObj->position.getPos0() + directionToFlag <= 14 &&
           (temp->isEmpty || (movebleObj->capitalCase != temp->capitalCase)) && temp->className != "mountains") {

    int y = movebleObj->position.getPos0() + directionToFlag;

    tuple<int, int> pos = make_tuple(y, movebleObj->position.getPos1());

    Position *to = new Position(pos);

    Position *from = new Position(movebleObj->position);

    action0.setFrom(*from);
    action0.setTo(*to);


}


return action0;
}

Action actionPlayerOne(World &world) {
// TODO Implement some basic strategy and remove the lines below
Action action1;

int x = (rand() % world.groupOfItems.size() + 1);

if (x == world.groupOfItems.size()) { x--; }

tuple<int, int> pos;
if (world.groupOfItems[x]->position.getPos0() - 1 >= 0) {
    tuple<int, int> pos = make_tuple(world.groupOfItems[x]->position.getPos0() - 1,
                                     world.groupOfItems[x]->position.getPos1());

    Position *posit = new Position(pos);
    shared_ptr<Item> temp = world.world[posit->getPos0()][posit->getPos1()];

    if (temp == world.world[8][6]) {
        cout << "WOOOW!!! Capital symbol found the portal!!!" << endl;
        Position *posit = new Position(world.world[0][0]->position);
        return Action(world.groupOfItems[x]->position, *posit);
    } else if (temp->isEmpty || temp->capitalCase != world.groupOfItems[x]->capitalCase)
        return Action(world.groupOfItems[x]->position, *posit);

}
if (world.groupOfItems[x]->position.getPos1() - 1 >= 0) {
    tuple<int, int> pos = make_tuple(world.groupOfItems[x]->position.getPos0(),
                                     world.groupOfItems[x]->position.getPos1() - 1);

    Position *posit = new Position(pos);
    shared_ptr<Item> temp = world.world[posit->getPos0()][posit->getPos1()];


    if (temp == world.world[8][6]) {
        cout << "WOOOW!!! Capital symbol found the portal!!!" << endl;
        Position *posit = new Position(world.world[0][0]->position);
        return Action(world.groupOfItems[x]->position, *posit);
    } else if (temp->isEmpty || temp->capitalCase != world.groupOfItems[x]->capitalCase)
        return Action(world.groupOfItems[x]->position, *posit);
}
if (world.groupOfItems[x]->position.getPos0() + 1 <= 14) {
    tuple<int, int> pos = make_tuple(world.groupOfItems[x]->position.getPos0() + 1,
                                     world.groupOfItems[x]->position.getPos1());

    Position *posit = new Position(pos);
    shared_ptr<Item> temp = world.world[posit->getPos0()][posit->getPos1()];

    if (temp == world.world[8][6]) {
        cout << "WOOOW!!! Capital symbol found the portal!!!" << endl;
        Position *posit = new Position(world.world[0][0]->position);
        return Action(world.groupOfItems[x]->position, *posit);
    } else if (temp->isEmpty || temp->capitalCase != world.groupOfItems[x]->capitalCase)
        return Action(world.groupOfItems[x]->position, *posit);

}


if (true) {
    return actionPlayerOne(world);
}
}

/**
* The return is a pair: action and a boolean whether a timeout happened
*/

std::tuple<Action, bool> waitPlayer(Action (&f)(World &w), World &world) {
auto start = std::chrono::high_resolution_clock::now();
// TODO Important. Below, action should be the result of calling the function passed as parameter
Action action = f(world);
auto end = std::chrono::high_resolution_clock::now();
std::chrono::duration<double, std::milli> elapsed = end - start;
// TODO This line can be removed
if (elapsed.count() > TIMEOUT) // if time > 0.3 s
    return {action, true}; // player failed to answer in less than 400 ms
else return {action, false};
}

int main() {
int n1, n2, n3, n4;
srand(time(NULL));
n1 = n2 = n3 = n4 = 10;

World world1(n1, n2, n3, n4);

World &world = world1;
cout << "Initial State" << endl;

world.printWorld();

// TODO Initialize the world

bool endGame = false;
cout << "-----------------------------" << endl;
cout << endl;
int stepOfGame = 1;
while (!endGame) {

    auto[action0, timeout0] = waitPlayer(actionPlayerZero, world);

    auto[action1, timeout1] = waitPlayer(actionPlayerOne, world);

    if (timeout0 || timeout1) {
        if (timeout0) { cout << "Time's zero player is up!" << endl; }
        else if (timeout1) { cout << "Time's first player is up!" << endl; }
        endGame = true;

        // TODO Show the result of the game. Who caused the timeout?
    } else {

        endGame = world.validateTheAction(action0, action1);
        cout << "#" << stepOfGame << endl;
        stepOfGame++;

        world.printWorld();
        cout << "-----------------------------" << endl;
        cout << endl;

        // TODO Validate the actions: actionPlayer0 and actionPlayer1
        // TODO Update the world
        // TODO Show the world
        // TODO End the game and show the result if a player won
    }
}
return 0;
}