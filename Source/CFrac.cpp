/*
  ==============================================================================

    CFrac.cpp
    Created: 3 Jul 2019 2:51:53am
    Author:  timcsy

  ==============================================================================
*/

#include "CFrac.h"
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
using namespace std;
using namespace CFrac;

double CFrac::mod(double a, double n, double eps) {
    double q = floor(a / n);
    return a - q * n;
}

double CFrac::quotient(double a, double n, double eps) {
    return (a - mod(a, n, eps)) / n;
}

void CFrac::real_to_conti(double r, vector<long long>& v, int precision, double eps) {
    if (precision == -1) return;
    v.push_back(r - mod(r, 1.0));
    if (mod(r, 1.0) < eps) return;
    real_to_conti(1 / mod(r, 1.0), v, precision - 1);
}

Q CFrac::conti_to_rational(vector<long long>& v) {
    Q n;
    n.p = 1;
    n.q = 0;
    for (int i = (int)v.size() - 1; i >= 0; i--) {
        long long p = n.p;
        n.p = v[i] * p + n.q;
        n.q = p;
    }
    return n;
}

void CFrac::rational_to_conti(Q n, vector<long long>& v, int precision) {
    if (precision == -1) return;
    if (n.q == 1) {
        v.push_back(n.p);
        return;
    }
    v.push_back(quotient(n.p, n.q));
    Q m;
    m.p = n.q;
    m.q = n.p - quotient(n.p, n.q) * n.q;
    rational_to_conti(m, v, precision - 1);
}

string CFrac::to_real_string(Q n) {
    string s;
    stringstream ss;
    ss << setprecision((log(n.p * n.q)) / log(10)) << (long double) n.p / n.q << endl;
    ss >> s;
    return s;
}

string CFrac::to_conti_string(vector<long long>& v) {
    string s;
    stringstream ss;
    if (v.size() >= 1) ss << "[" << v[0] << ";";
    for (int i = 1; i < v.size() - 1; i++) ss << v[i] << ",";
    if (v.size() > 1) ss << v[v.size() - 1] << "]";
    else ss << "]";
    ss >> s;
    return s;
}

string CFrac::to_rational_string(Q n) {
    string s;
    stringstream ss;
    ss << n.p << "/" << n.q << endl;
    ss >> s;
    return s;
}

double CFrac::from_real_string(string s, double zero) {
    double a = atof(s.c_str());
    return a;
}

vector<long long> CFrac::from_conti_string(string s, int precision, long long zero) {
    s = s.substr(1, s.length() - 2);
    vector<long long> tokens;
    size_t prev = 0, pos = 0;
    
    pos = s.find(";", prev);
    if (pos == string::npos) pos = s.length();
    long long token = atoi(s.substr(prev, pos-prev).c_str());
    tokens.push_back(token);
    prev = pos + 1;
    
    while (pos < s.length() && prev < s.length()) {
        pos = s.find(",", prev);
        if (pos == string::npos) pos = s.length();
        long long token = atoi(s.substr(prev, pos-prev).c_str());
        tokens.push_back(token);
        prev = pos + 1;
    }
    
    if (precision >= tokens.size()) precision = (int)tokens.size() - 1;
    vector<long long> sub_tokens(tokens.begin(), tokens.begin() + precision + 1);
    return sub_tokens;
}

Q CFrac::from_rational_string(string s, long long zero) {
    Q n;
    size_t pos = s.find("/", 0);
    n.p = atoi(s.substr(0, pos).c_str());
    n.q = atoi(s.substr(pos + 1, s.length() - pos -1).c_str());
    return n;
}

double CFrac::get_closest(double r, double error) {
    Q n;
    int precision = 0;
    while (precision < 1000) {
        vector<long long> v;
        real_to_conti(r, v, precision);
        n = conti_to_rational(v);
        if (n.q >= 0 && n.q >= 1) {
            double cf = (double)n.p / (double)n.q;
            if (-error <= cf - r && cf - r <= error) return cf;
        }
        precision++;
    }
    return 0;
}
