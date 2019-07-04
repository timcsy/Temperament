/*
  ==============================================================================

    CFrac.h
    Created: 1 Jul 2019 5:54:34pm
    Author:  timcsy

  ==============================================================================
*/

#pragma once

#include <vector>
using namespace std;

namespace CFrac {
    
    struct Q { // p/q
        long long p;
        long long q;
    };
    
    double mod(double a, double n, double eps = 1e-10);
    
    double quotient(double a, double n, double eps =  1e-10);
    
    void real_to_conti(double r, vector<long long>& v, int precision = 100, double eps = 1e-10);
    
    Q conti_to_rational(vector<long long>& v);
    
    void rational_to_conti(Q n, vector<long long>& v, int precision = 100);
    
    string to_real_string(Q n);
    
    string to_conti_string(vector<long long>& v);
    
    string to_rational_string(Q n);
    
    double from_real_string(string s, double zero);
    
    vector<long long> from_conti_string(string s, int precision, long long zero);
    
    Q from_rational_string(string s, long long zero);
    
    double get_closest(double r, double error);
}
