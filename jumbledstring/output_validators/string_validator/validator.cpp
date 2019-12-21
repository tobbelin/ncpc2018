#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#include "validate.h"

using namespace std;

void assert_done(istream& is) {
	try {
		string dummy;
		is >> dummy;
		wrong_answer("extraneous data: " + dummy);
	} catch(...) {}
}

int main(int argc, char** argv) {
	init_io(argc, argv);

	string judge_answer, author_answer;
	judge_ans >> judge_answer;

	author_out.exceptions(author_out.failbit | author_out.badbit);
  	try {
    	author_out >> author_answer;
    	transform(author_answer.begin(),author_answer.end(),author_answer.begin(),::tolower);
    	if (judge_answer == "impossible") {
    		if (author_answer != "impossible") {
    			wrong_answer("Impossible scenario not detected");
    		}
    	} else {
    		if (author_answer.size() > 1000000) {
    			wrong_answer("Too long answer");
    		}
    		int c00, c01, c10, c11;
    		judge_in >> c00 >> c01 >> c10 >> c11;
    		int u00 = 0, u01 = 0, u10 = 0, u11 = 0;
    		int u0 = 0, u1 = 0;
    		for (auto bit : author_answer) {
    			if (bit == '0') {
    				u00 += u0;
    				u10 += u1;
    				u0++;
    			} else if (bit == '1') {
    				u01 += u0;
    				u11 += u1;
    				u1++;
    			} else {
    				wrong_answer("Invalid character");
    			}
    		}
    		if (c00 != u00 || c01 != u01 || c10 != u10 || c11 != u11) {
    			wrong_answer("Invalid subsequence count");
    		}
    	}

	    assert_done(author_out);

    	accept();
  	} catch(...) {
    	wrong_answer("IO failure");
  	}
}
