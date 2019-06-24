#pragma once

#include "date.h"

#include <map>
#include <vector>
#include <memory>
using namespace std;

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum class LogicalOperation {
    And,
    Or,
};

class Node {
public:
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
    virtual ~Node() {}
};

class EmptyNode : public Node {
public:
    bool Evaluate(const Date& date, const string& event) const override {
        return true;
    }
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(Comparison cmp, const Date& date)
        : cmp_(cmp)
        , date_(date)
    {}

    bool Evaluate(const Date& date, const string& event) const override {
        if(cmp_ == Comparison::Less) {
            return date < date_;
        } else if (cmp_ == Comparison::LessOrEqual) {
            return date <= date_;
        } else if (cmp_ == Comparison::Greater) {
            return date > date_;
        } else if (cmp_ == Comparison::GreaterOrEqual) {
            return date >= date_;
        } else if (cmp_ == Comparison::Equal) {
            return date == date_;
        } else /*if (cmp_ == Comparison::NotEqual)*/ {
            return date != date_;
        }
    }
private:
    Comparison cmp_;
    Date date_;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(Comparison cmp, const string& event)
        : cmp_(cmp)
        , event_(event)
    {}

    bool Evaluate(const Date& date, const string& event) const override {
        if (cmp_ == Comparison::Equal) {
            return event == event_;
        } else if (cmp_ == Comparison::NotEqual) {
            return event != event_;
        } else if(cmp_ == Comparison::Less) {
            return event < event_;
        } else if (cmp_ == Comparison::LessOrEqual) {
            return event <= event_;
        } else if (cmp_ == Comparison::Greater) {
            return event > event_;
        } else /*if (cmp_ == Comparison::GreaterOrEqual) */{
            return event >= event_;
        }
    }
private:
    Comparison cmp_;
    string event_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(LogicalOperation logical_operation, shared_ptr<Node> left, shared_ptr<Node> rigth)
        : logical_operation_(logical_operation)
        , left_(left)
        , rigth_(rigth)
    {}

    bool Evaluate(const Date& date, const string& event) const override {
        if(logical_operation_ == LogicalOperation::And) {
            return left_->Evaluate(date, event) && rigth_->Evaluate(date, event);
        } else /*if(logical_operation_ == LogicalOperation::Or)*/ {
            return left_->Evaluate(date, event) || rigth_->Evaluate(date, event);
        }
    }
private:
    LogicalOperation logical_operation_;
    shared_ptr<const Node> left_, rigth_;
};
