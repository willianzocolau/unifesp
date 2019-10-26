#include <bits/stdc++.h>

using namespace std;

class Matrix {
    public:
        int index, validate;
};

vector<Matrix> input(int *n, int *m, vector<Matrix> &matrix, vector<int> &candidates) {
    cin >> *n >> *m;
    matrix = vector<Matrix>(*n);
    candidates = vector<int>(*n);

    for (int i = 0; i < *n; i++) {
        candidates[i] = i;
    }

    int x, y;
    for (int i = 0; i < *m; i++) {
        cin >> x >> y;
        matrix[y - 1].index = x - 1;
        matrix[y - 1].validate = 1;
        candidates.erase(std::remove(candidates.begin(), candidates.end(), (x - 1)), candidates.end());
    }

    return matrix;
}

void print_solution(vector<Matrix> &matrix) {
    cout << matrix[0].index + 1;
    for (int i = 1; i < matrix.size(); i++) {
        cout << " " << matrix[i].index + 1;;
    }
    cout << endl;
}

int is_solution(vector<Matrix> &matrix, int k, vector<int> &candidates) {
    if (k == matrix.size() - 1) return 1;
    else if (candidates.size() == 0) return 1;
    else return 0;
}

void process_solution(vector<Matrix> &matrix) {
    int n = matrix.size();
    set<int> s;
    for (int i = 0; i < n; i++) {
        s.insert(matrix[i].index);
    }

    if (s.size() == matrix.size())
        print_solution(matrix);
}

int make_move(vector<Matrix> &matrix, int i, int k, vector<int> &candidates) {
    int save = candidates[i];
    matrix[k].validate = 1;
    candidates.erase(candidates.begin() + i);
    return save;
}

void unmake_move(vector<Matrix> &matrix, int i, int k, vector<int> &candidates, int save) {
    candidates.insert(candidates.begin() + i, save);
    matrix[k].validate = 0;
}

void apply_backtrack(vector<Matrix> &matrix, int k, vector<int> &candidates) {
    if (is_solution(matrix, k, candidates)) {
        process_solution(matrix);
    } else {
        k++;
        for (int i = 0; i < candidates.size(); i++) {
            while (matrix[k].validate == 1) k++;
            matrix[k].index = candidates[i];
            int save = make_move(matrix, i, k, candidates);
            apply_backtrack(matrix, k, candidates);
            unmake_move(matrix, i, k, candidates, save);
        }
    }
}

int main() {
    int n, m;
    vector<Matrix> matrix;
    vector<int> candidates;
    input(&n, &m, matrix, candidates);
    apply_backtrack(matrix, -1, candidates);
    return 0;
}


