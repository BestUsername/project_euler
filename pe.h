#ifndef PE_H
#define PE_H

#include <cstdlib>
#include <sstream>
#include <time.h>

class pe_base {
    public:
        void go() {
            clock_t timer = clock();
            this->run_test();
            timer = clock() - timer;
            m_timing = ((double) timer)/CLOCKS_PER_SEC;
            m_message << " (" << m_timing << "s)"; 
        }

        bool get_result() { return m_result; };
        std::string get_message() { return m_message.str(); };
        double get_timing() { return m_timing; };
        int exit_code() { return m_result ? EXIT_SUCCESS : EXIT_FAILURE; };

    protected:
        virtual void run_test() = 0;

        template<typename T>
        void check(std::string name, T answer, T value) {
            m_result = answer == value;
            m_message << name << ": ";
            if (!m_result) {
                m_message << "FAIL - value(" << value << ") does not match answer(" << answer << ")";
            } else {
                m_message << "PASS";
            }
        };

    private:
        std::stringstream m_message;
        bool m_result;
        double m_timing;
};

#endif//PE_H
