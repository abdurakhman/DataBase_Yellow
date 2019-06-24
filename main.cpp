#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"
#include "tests.h"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <sstream>

using namespace std;

string ParseEvent(istream& is) {
    string event;
    while(is.peek() == ' ')
        is.ignore(1);
    getline(is, event);
    return event;
}

void TestAll();

int main() {
    TestAll();

    Database db;

    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(cout);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }
    }



    return 0;
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
    tr.RunTest(TestDatabase, "TestDatabase");
    tr.RunTest(TestDatabasePrint, "TestDatabasePrint");
    tr.RunTest(TestDatabaseDel, "TestDatabaseDel");
    tr.RunTest(TestDatabaseLast, "TestDatabaseLast");
    tr.RunTest(TestDatabaseFind, "TestDatabaseFind");
    tr.RunTest(TestDateComparisonNode, "TestDateComparisonNode");
    tr.RunTest(TestEventComparisonNode, "TestEventComparisonNode");
    tr.RunTest(TestLogicalOperationNode, "TestLogicalOperationNode");
    tr.RunTest(TestEmptyNode, "TestEmptyNode");
    tr.RunTest(TestParseDate, "TestParseDate");
    tr.RunTest(TestDateComparison, "TestDateComparison");
    tr.RunTest(TestDbAdd, "TestDbAdd");
    tr.RunTest(TestDbFind, "TestDbFind");
    tr.RunTest(TestDbLast, "TestDbLast");
    tr.RunTest(TestDbRemoveIf, "TestDbRemoveIf");
    tr.RunTest(TestDate, "TestDate");
}



