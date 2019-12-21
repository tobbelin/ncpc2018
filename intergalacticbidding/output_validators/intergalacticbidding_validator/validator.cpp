#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <cmath>
#include <vector>
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

	int judge_count, author_count;
    vector<string> judge_list, author_list;
	judge_ans >> judge_count;
    for (int i = 0; i < judge_count; i++) {
        string name;
        judge_ans >> name;
        judge_list.push_back(name);
    }

	author_out.exceptions(author_out.failbit | author_out.badbit);
  	try {
    	author_out >> author_count;
    	if (author_count != judge_count) {
            wrong_answer("Incorrect number of winners");
    	} else {
            for (int i = 0; i < judge_count; i++) {
                string name;
                author_out >> name;
                author_list.push_back(name);
            }
            sort(judge_list.begin(), judge_list.end());
            sort(author_list.begin(), author_list.end());
            for (int i = 0; i < judge_count; i++) {
                if (judge_list[i] != author_list[i]) {
                    wrong_answer("Incorrect list of winners");
                }
            }
    	}

	    assert_done(author_out);

    	accept();
  	} catch(...) {
    	wrong_answer("IO failure");
  	}
}
