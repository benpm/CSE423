#include <iostream>
#include <queue>
#include "parsetree.hpp"

void Tree::print()
{
    // Keep track of current node
    ParseTree cur = this;

    int row_cnt = 0;
    int cnt = 1;

    // Create a queue for BFS 
    std::queue<ParseTree> q; 
    std::queue<int> child_cnt;
  
    // Enqueue the current node
    q.push(cur); 
  
    while(!q.empty()) { 
        // Dequeue a vertex from queue and print it 
        cur = q.front();
        q.pop(); 

        cnt--;
        
        if (cur->value != Tree::Terminal::NONE) {
            if (cnt > 0)
                std::cout << Tree::terminalStr[cur->value] << "   ";
            else
                std::cout << Tree::terminalStr[cur->value] << "\n";
        } else {
            if (cnt > 0)
                std::cout << Tree::nonTerminalStr[cur->identifier] << "   ";
            else
                std::cout << Tree::nonTerminalStr[cur->identifier] << "\n";
        }
  
        // Get all child nodes of the current node
        row_cnt += cur->nodes.size();
        for (auto i = cur->nodes.begin(); i != cur->nodes.end(); i++)
            q.push(*i); 

        if (cnt == 0) {
            cnt = row_cnt;
            row_cnt = 0;
        }
    } 
}
