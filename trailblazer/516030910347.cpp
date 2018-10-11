
#include "Trailblazer.h"
#include "queue.h"
#include "priorityqueue.h"
using namespace std;

static const double SUFFICIENT_DIFFERENCE = 0.2;

Path breadthFirstSearch(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    Map<string, int> visit;   //map to store the visited places
    Queue<Vector<RoadNode*>> q;   //queue to store the pathes
        Vector<RoadNode*> s;
        start->setColor(Color::YELLOW);
        s.push_back(start);
        if (start == end) {
            start->setColor(Color::GREEN);
            return s;
        }
        visit.add(start->nodeName() , 1);
        q.add(s);
        while (q.isEmpty()==false) {
            s = q.front();
            int sz=s.size();
            RoadNode* begin = s[sz-1];   //just like top() in a stack
            begin->setColor(Color::GREEN);
            q.dequeue();
            Set<RoadNode*> se = graph.neighborsOf(begin);
            set<RoadNode*> nei=se.toStlSet();
            set<RoadNode*>::iterator it;
            if (nei.empty()==false){
            for (it = nei.begin(); it != nei.end();it++) {
                Vector<RoadNode*> t = s;
                RoadNode* cur = *it;
               if (visit.containsKey(cur->nodeName())==false) {
                    cur->setColor(Color::YELLOW);
                    visit.add(cur->nodeName(), 1);
                    t.push_back(cur);
                    q.add(t);
                    if (cur == end) {
                        cur->setColor(Color::GREEN);
                        return t;
                    }
                }
            }
            }
        }

        Vector<RoadNode*>v; //if queue is empty,there is no path
        return v;
}

Path dijkstrasAlgorithm(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    Map<string, int> visit;
        PriorityQueue<Vector<RoadNode*>> q{};
        Vector<RoadNode*> s;
        s.push_back(start);
        start->setColor(Color::YELLOW);
        if (start == end) {
            start->setColor(Color::GREEN);
            return s;
      }
        visit.add(start->nodeName(),1);
        double prio=0;
        q.add(s,prio);   //when start enqueues,the cost is 0
        while (q.isEmpty()==false) {
            s = q.front();
            double pri=q.peekPriority();   //the shortest of the queue
            int sz=s.size();
            RoadNode* begin= s[sz-1];
            begin->setColor(Color::GREEN);
            q.dequeue();

            Set<RoadNode*> se = graph.neighborsOf(begin);
            set<RoadNode*> nei=se.toStlSet();
            set<RoadNode*>::iterator it;
            if (nei.empty()==false){

            for (it = nei.begin(); it != nei.end();it++) {
                prio=pri;       //copy for future use
                Vector<RoadNode*> t = s;
                RoadNode* cur_node=*it;
                if (visit.containsKey(cur_node->nodeName())==false) {
                    visit.add(cur_node->nodeName(), 1);
                    cur_node->setColor(Color::YELLOW);
                    t.push_back(cur_node);
                    RoadEdge* edge=graph.edgeBetween(begin,cur_node);
                    prio+=edge->cost();        // change prio
                    q.add(t,prio);
                    }
                }
              }
            int siz=q.front().size();
            RoadNode* now_best=q.front()[siz-1];
            if (now_best == end) {     //check until all the next node is visited
                now_best->setColor(Color::GREEN);
                return q.front();
            }

        }

        Vector<RoadNode*>v;
        return v;
}

