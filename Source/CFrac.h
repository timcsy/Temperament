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
    
    template <class N>
    struct Q { // p/q
        N p;
        N q;
    };
    
    template <class R>
    R mod(R a, R n, R eps = (R)1e-10) {
        if (a > n - eps) return mod(a - n, n);
        else if (a < -eps) return mod(a + n, n);
        else return a;
    }
    
    template <class R>
    R quotient(R a, R n, R eps = (R)1e-10) {
        return (a - mod(a, n, eps)) / n;
    }
    
    template <class N, class R>
    void real_to_conti(R r, vector<N>& v, int precision = 100, R eps = 1e-10) {
        if (precision == -1) return;
        v.push_back(r - mod(r, 1.0));
        if (mod(r, 1.0) < eps) return;
        real_to_conti(1 / mod(r, 1.0), v, precision - 1);
    }
    
    template <class N>
    Q<N> conti_to_rational(vector<N>& v) {
        Q<N> n;
        n.p = 1;
        n.q = 0;
        for (int i = (int)v.size() - 1; i >= 0; i--) {
            N p = n.p;
            n.p = v[i] * p + n.q;
            n.q = p;
        }
        return n;
    }
    
    template <class N>
    void rational_to_conti(Q<N> n, vector<N>& v, int precision = 100) {
        if (precision == -1) return;
        if (n.q == 1) {
            v.push_back(n.p);
            return;
        }
        v.push_back(quotient(n.p, n.q));
        Q<N> m;
        m.p = n.q;
        m.q = n.p - quotient(n.p, n.q) * n.q;
        rational_to_conti(m, v, precision - 1);
    }
    
    template <class N>
    string to_real_string(Q<N> n) {
        string s;
        stringstream ss;
        ss << setprecision((log(n.p * n.q)) / log(10)) << (long double) n.p / n.q << endl;
        ss >> s;
        return s;
    }
    
    template <class N>
    string to_conti_string(vector<N>& v) {
        string s;
        stringstream ss;
        if (v.size() >= 1) ss << "[" << v[0] << ";";
        for (int i = 1; i < v.size() - 1; i++) ss << v[i] << ",";
        if (v.size() > 1) ss << v[v.size() - 1] << "]";
        else ss << "]";
        ss >> s;
        return s;
    }
    
    template <class N>
    string to_rational_string(Q<N> n) {
        string s;
        stringstream ss;
        ss << n.p << "/" << n.q << endl;
        ss >> s;
        return s;
    }
    
    template <class R>
    R from_real_string(string s, R zero) {
        R a = atof(s.c_str());
        return a;
    }
    
    template <class N>
    vector<N> from_conti_string(string s, int precision, N zero) {
        s = s.substr(1, s.length() - 2);
        vector<N> tokens;
        size_t prev = 0, pos = 0;
        
        pos = s.find(";", prev);
        if (pos == string::npos) pos = s.length();
        N token = atoi(s.substr(prev, pos-prev).c_str());
        tokens.push_back(token);
        prev = pos + 1;
        
        while (pos < s.length() && prev < s.length()) {
            pos = s.find(",", prev);
            if (pos == string::npos) pos = s.length();
            N token = atoi(s.substr(prev, pos-prev).c_str());
            tokens.push_back(token);
            prev = pos + 1;
        }
        
        if (precision >= tokens.size()) precision = tokens.size() - 1;
        vector<N> sub_tokens(tokens.begin(), tokens.begin() + precision + 1);
        return sub_tokens;
    }
    
    template <class N>
    Q<N> from_rational_string(string s, N zero) {
        Q<N> n;
        size_t pos = s.find("/", 0);
        n.p = atoi(s.substr(0, pos).c_str());
        n.q = atoi(s.substr(pos + 1, s.length() - pos -1).c_str());
        return n;
    }
    
    int note_num(int overtune1, int overtune2, int precision, int max) {
        double r = log(overtune1) / log(overtune2);
        if (r < 1) r = 1 / r;
        vector<long long int> v;
        real_to_conti(r, v, precision);
        Q<long long int> n = conti_to_rational(v);
        return (int)n.q;
    }
}
