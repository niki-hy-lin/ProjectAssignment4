#include "path.h"
#include <queue>
#include <stack>
using namespace std;

path::path(const PNG & im, pair<int,int> s, pair<int,int> e) {
	start = s;
	end = e;
	image = im;
	BFS();
}

void path::BFS(){
	vector<vector<bool>> V(image.height(), vector<bool> (image.width(),false));
	vector<vector<pair<int,int>>> P(image.height(), vector<pair<int,int>> (image.width(),end));
	queue<pair<int,int>> locationQ;

	V[start.second][start.first] = true;
	P[start.second][start.first] = start;
	locationQ.push(start);

	/* your code here */
	pair<int,int> u;
	vector<pair<int,int>> n;

	while (!locationQ.empty()){
		u = locationQ.front;
		locationQ.pop();
		n = neighbors (u);

		for (int i = 0; i < n. size() ; i++) {
			if (good(V, u, n[i] )) {
				/* code */
				V[n[i].second][n[i].first] = true;
				locationQ.push(n[i]);

				P[n[i].second][n[i].first] = u;
			}
		}

	}

	pathPts = assemble(P,start,end);
}

PNG path::render(){

	pair <int, int> point;
	RGBAPixel red = RGBAPixel (255, 0, 0);
	PNG drawReds(image);

	for (int i = 0; i < pathPts.size(); i++) {
		point = pathPts[i];

		*(drawReds.getPixel(point.first, point.second)) = red;
	}

	return drawReds;

}

bool path::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){
    /* your code here */
		if (0 <= next.first && next.first < image.width() &&
	      0 <= next.second && next.second <image.height()) {

			if (v[next.second][next.first] == false) {

				if (
						closeEnough(*(image.getPixel(curr.first,curr.second)),
												*(image.getPixel(next.first,next.second)))
						) {
					return true;
				}
			}
		}
		return false;
}


vector<pair<int,int>> path::neighbors(pair<int,int> curr) {
	vector<pair<int,int>> n;

  n.push_back (pair<int,int> (curr.first + 1, curr.second));
	n.push_back (pair<int,int> (curr.first, curr.second + 1));
	n.push_back (pair<int,int> (curr.first, curr.second - 1));
	n.push_back (pair<int,int> (curr.first - 1, curr.second));

	return n;

}

vector<pair<int,int>> path::assemble(vector<vector<pair<int,int>>> & p,pair<int,int> s, pair<int,int> e) {
	vector<pair<int,int>> allPts;
	stack<pair<int,int>> resultStack;

	pair<int,int> pred;
	pair<int,int> curr = e;

	resultStack.push(e);

	while (curr!= s) {
			pred = p [curr.second][curr.first];

			if(pred == end) {
				allPts.clear();
				allPts.push_back(s);
				return allPts;
			}

			resultStack.push(pred);
			curr = pred;
	}

	while (!resultStack.empty()) {
		allPts.push_back(resultStack.top());
		resultStack.pop();
	}

	return allPts;
}


/* PA4 - Completed for you for 2018S Semester */

bool path::closeEnough(RGBAPixel p1, RGBAPixel p2){
	int dist = (p1.r-p2.r)*(p1.r-p2.r);
	dist    += (p1.g-p2.g)*(p1.g-p2.g);
	dist    += (p1.b-p2.b)*(p1.b-p2.b);
	return (dist <= 80);
}

vector<pair<int,int>> path::getPath() {
	return pathPts;
}

int path::length() {
	return pathPts.size();
}
