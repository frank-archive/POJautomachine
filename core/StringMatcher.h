#pragma once
#include<string>
#include<cstring>
#include<cstdlib>
int kmp(const char *text, const char *find) {
	if (*text == '/0' || *find == '/0') return -1;
	int find_len = strlen(find);
	int text_len = strlen(text);
	int *map;
	if (text_len < find_len) return -1;
	map = (int*)malloc(sizeof(int)*find_len);
	memset(map, 0, find_len * sizeof(int)); //initial the kmp base array: map 
	map[0] = 0; map[1] = 0;
	int i = 2; int j = 0;
	for (i = 2; i< find_len; i++) {
		while (1) {
			if (find[i - 1] == find[j]) {
				j++;
				if (find[i] == find[j]) {
					map[i] = map[j];
				}
				else  map[i] = j;
				break;
			}
			else {
				if (j == 0) {
					map[i] = 0;
					break;
				}
				j = map[j];
			}
		}
	}
	i = 0;
	j = 0;
	for (i = 0; i<text_len;) {
		if (text[i] == find[j]) {
			i++;
			j++;
		}
		else {
			j = map[j];
			if (j == 0) i++;
		}
		if (j == (find_len)) return i - j;
	}
	return -1;
}
using namespace std;
int match(string &src, string &pat) {
	return kmp(src.c_str(), pat.c_str());
}