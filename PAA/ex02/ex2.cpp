#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int max_subarray(vector<int> time_musics, int expected_time_music) {
  int left = 0, right = time_musics.size() - 1;
  int diff_result = abs(time_musics[left] + time_musics[right] - expected_time_music);
  int flag = 0;

  while (left < right) {
    int soma = time_musics[left] + time_musics[right];
    int diff = abs(soma - expected_time_music);

    if (diff <= diff_result && soma <= expected_time_music) {
      diff_result = diff;
      flag = 1;
      left++;
    } else if (time_musics[left] + time_musics[right] < expected_time_music) left++;
    else right--;
  }

  if (flag == 1) return diff_result;
  else return -1;
}

int main() {
  int qtd_music = 0, expected_time_music = 0;;
  vector<int> time_musics;
  cin >> qtd_music >> expected_time_music;

  for (int i = 0; i < qtd_music; i++) {
    int temp;
    cin >> temp;
    time_musics.push_back(temp);
  }

  sort(time_musics.begin(), time_musics.end());
  int soma = max_subarray(time_musics, expected_time_music);
  if (soma == -1) cout << "NONE" << endl;
  else cout << expected_time_music - soma << endl;
  return 0;
}