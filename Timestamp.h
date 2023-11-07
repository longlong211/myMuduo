#pragma once 
#include<iostream>
#include<string>
class Timestamp{
    public:
    Timestamp();
    explicit Timestamp(int64_t microSecondsSinceEpoch_);
    static Timestamp now();
    std::string toSTring()const;
    private:
    int64_t microSecondsSinceEpoch_;
};