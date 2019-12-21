#include "validate.h"
#include <regex>

using namespace std;

int main(int argc, char **argv) {
    init_io(argc, argv);

    int n, m, rounds = 0, no_matches = 0;
    judge_in >> n >> m;

    bool played[m][n][m][n];
    memset(played, 0, sizeof(played));

    regex match_regex("([A-Za-z])([0-9]+)-([A-Za-z])([0-9]+)");
    string line;
    while (getline(author_out, line)) {
        rounds++;
        istringstream iss(line);
        string match;
        bool pr[m][n];
        memset(pr, 0, sizeof(pr));
        while (iss >> match) {
            cout << match << endl;
            smatch mr;
            if (!regex_match(match, mr, match_regex)) {
                wrong_answer("Invalid match format in round %d: %s", rounds, match.c_str());
            }
            char c1 = mr[1].str()[0], c2 = mr[3].str()[0];
            int t1 = (c1 >= 'A' && c1 <= 'Z') ? (c1 - 'A') : (c1 - 'a');
            int t2 = (c2 >= 'A' && c2 <= 'Z') ? (c2 - 'A') : (c2 - 'a');
            int p1 = atoi(mr[2].str().c_str()) - 1, p2 = atoi(mr[4].str().c_str()) - 1;
            if (t1 < 0 || t2 < 0 || t1 >= m || t2 >= m || p1 < 0 || p2 < 0 || p1 >= n || p2 >= n) {
                wrong_answer("Invalid player reference in round %d: %s", rounds, match.c_str());
            }
            if (t1 == t2) {
                wrong_answer("Round %d: %s: Players from same team should not play against each other", rounds, match.c_str());
            }
            if (played[t1][p1][t2][p2]) {
                wrong_answer("Round %d: %s: Players have already played against each other", rounds, match.c_str());
            }
            if (pr[t1][p1] || pr[t2][p2]) {
                wrong_answer("Round %d: %s: Players have already played in this round", rounds, match.c_str());
            }
            pr[t1][p1] = true;
            pr[t2][p2] = true;
            played[t1][p1][t2][p2] = true;
            played[t2][p2][t1][p1] = true;
            no_matches++;
        }
    }

    if (rounds > n * (m-1) + 1) {
        wrong_answer("Too many rounds! Solution had %d rounds, but only %d allowed.", rounds, n * (m-1) + 1);
    }
    if (no_matches != m*n*(m-1)*n/2) {
        wrong_answer("There are %d matches missing in the schedule!", m*n*(m-1)*n/2 - no_matches);
    }
    accept();
}
