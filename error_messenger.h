#pragma once

#include <iostream>
#include <vector>

class ErrorMessenger
{
    std::vector<std::string> messages;
    unsigned int errors_cnt;

    ErrorMessenger() : errors_cnt(0)
    {}
    ErrorMessenger(const ErrorMessenger& source) = delete;
    ErrorMessenger& operator=(const ErrorMessenger& rhs) = delete;

public:

    static ErrorMessenger& get_instance(){
        static ErrorMessenger instance;
        return instance;
    }

    void report(std::string msg){
        messages.push_back(msg);
        errors_cnt++;
    }

    void print_report(std::ostream& os){
        os << "Errors : " << errors_cnt << '\n';
        for(auto msg : messages)
            os << msg << '\n';
    }
};
