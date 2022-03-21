#include<iostream>
#include<iostream>
using namespace std;
int* getNextarray(string m) {
	if (m.length() == 0) return nullptr;
	int* ans = (int*)malloc(sizeof(int) * m.length());
	ans[0] = -1;
	if (m.length() == 1) return ans;
	ans[1] = 0;
	int i = 2;
	int cn = 0;
	while (i < m.length()) {
		if (m[i - 1] == m[cn]) {
			ans[i++] = ++cn;
		}else if (cn==0) {
			ans[i++] = 0;
		}else {
			cn = ans[cn];
		}
	}
	return ans;
}
int myKMP(string haystack, string needle) {
	if (needle.length() == 0) return 0;
	if (haystack.length() < needle.length()) return -1;
	int* next = getNextarray(needle);
	int i = 0, j = 0;
	while (i<haystack.length()&&j<needle.length()) {
		if (haystack[i] == needle[j]) {
			i++; j++;
		}
		else if (j == 0) {
			i++;
		}
		else {
			j = next[j];
		}
	}
	return (j == needle.length()) ? haystack.length() - j : -1;
}