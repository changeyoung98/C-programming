// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "Trailblazer.h"
#include <stack>;
#include <vector>;
#include <queue>;
#include <set>;
#include <map>;
#include <string>;
using namespace std;


static const double SUFFICIENT_DIFFERENCE = 0.2;

Path breadthFirstSearch(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
	/* TODO: Delete the following lines and implement this function! */

	Map<string, int> visit;
	Queue<Vector<RoadNode*>> q;
	Vector<RoadNode*> s;
	start->setColor(Color::YELLOW);
	s.push_back(start);
	if (&start == &end) {
		start->setColor(Color::GREEN);
		return s;
	}
	visit.add(start->nodeName(), 1);
	q.add(s);
	while (!q.isEmpty()) {
		Vector<RoadNode*> s = q.front();
		int sz = s.size();
		RoadNode* begin = s[sz - 1];
		Set<RoadNode*> se = graph.neighborsOf(begin);
		set<RoadNode*> nei = se.toStlSet();
		set<RoadNode*>::iterator it;
		for (it = nei.begin(); it != nei.end(); it++) {
			Vector<RoadNode*> t = s;
			RoadNode* cur = *it;
			cur->setColor(Color::YELLOW);
			if (!visit.containsKey(cur->nodeName())) {
				visit.add(cur->nodeName(), 1);
				t.push_back(cur);
				q.add(t);
				if (&cur == &end) {
					begin->setColor(Color::GREEN);
					cur->setColor(Color::GREEN);
					return s;
				}
			}
		}

		begin->setColor(Color::GREEN);
		q.dequeue();
	}

	Vector<RoadNode*>v;
	return v;
}

Path dijkstrasAlgorithm(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
	/* TODO: Delete the following lines and implement this function! */

	Map<string, int> visit;
	PriorityQueue<Vector<RoadEdge*>> q;
	Vector<RoadEdge*> s;
	start->setColor(Color::YELLOW);
	if (&start == &end) {
		Vector<RoadNode*> v;
		v.push_back(start);
		start->setColor(Color::GREEN);
		return v;
	}

	RoadEdge* first;
	s.add(first);
	visit.add(start->nodeName(), 1);
	double prio = 0;
	q.add(s, prio);
	while (!q.isEmpty()) {
		Vector<RoadEdge*> s = q.front();
		int sz = s.size();
		RoadNode* begin;
		begin = s[sz - 1]->to();
		if (begin == nullptr) {
			begin = start;
		}
		Set<RoadEdge*> se = begin->outgoingEdges();
		set<RoadEdge*> nei = se.toStlSet();
		set<RoadEdge*>::iterator it;
		for (it = nei.begin(); it != nei.end(); it++) {
			Vector<RoadEdge*> t = s;
			RoadEdge* cur = *it;
			RoadNode* cur_node = cur->to();
			cur_node->setColor(Color::YELLOW);
			if (!visit.containsKey(cur_node->nodeName())) {
				visit.add(cur_node->nodeName(), 1);
				t.push_back(cur);
				prio += cur->cost();
				q.add(t, prio);
			}
		}

		int siz = q.front().size();
		RoadEdge* now_best = q.front()[siz - 1];
		RoadNode* now_top = now_best->to();
		now_top->setColor(Color::GREEN);
		if (&now_top == &end) {
			Vector<RoadNode*> path;
			path.add(start);
			for (int i = 1; i<siz; i++) {
				path.add(q.front()[i]->to());
			}
			return path;
		}
		q.dequeue();
	}

	Vector<RoadNode*>v;
	return v;
}

