#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
const int mxa = 26;

vi prefix_function(string &S){
	int n = S.length();
	vi pi(n, 0);
	for(int i=1;i<n;i++){
		int j = pi[i-1];
		while(j>0 && S[j]!=S[i])
			j = pi[j-1];
		if(S[i]==S[j])j++;
		pi[i] = j;
	}
	return pi;
}

vector<vi> prefix_automata(string &S){
	int n = S.length();
	
	// Uses KMP to get the pi values
	vi pi = prefix_function(S);
	
	// The declaring graph/automata
	vector<vi> automata(n+1, vi(mxa, -1));
	
	// Initialization
	for(int i=0;i<mxa;i++)automata[0][i] = 0;
	automata[0][S[0]-'a'] = 1;
	
	// Creating the automata using the value from prefix function in O(26.N) time.
	// Graph indices are from 0 to n.
	// String indices are from 0 to n-1.
	/* 
	node 0 is the starting vertex, for staring matching we always start from node 0 and follow the edge according to the values 
	in the given string i.e. not the pattern string. the max value of c will give us the max prefix of pattern string that matches with given string.
	*/
	for(int i=0;i<n;i++){
		for(int c=0;c<mxa;c++){
			if((i+1)<n && S[i+1]==(c+'a'))automata[i+1][c] = i+2;
			else automata[i+1][c] = automata[pi[i]][c];
		}
	}
	return automata;
}

int main(){
	cin.tie(0)->sync_with_stdio(0);
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif

	string S; cin >> S;
	vector<vi> automata = prefix_automata(S);
	for(auto r: automata){
		for(auto e: r)cout << e << " ";
		cout << '\n';
	}
	return 0;
}
