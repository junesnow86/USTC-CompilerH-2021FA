/*
 * Bison输出结果生成语法树的辅助类
 */

#ifndef BAZINGA_COMPILER_SYNTAX_TREE_H
#define BAZINGA_COMPILER_SYNTAX_TREE_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include "ast_typedef.h"

typedef struct TreeNode {
    struct TreeNode *parent;
    struct std::vector<struct TreeNode *> children;
    std::string node_name;
    LL_AST_TYPE node_type;

public:
    TreeNode() {
        this->parent = nullptr;
        this->children = std::vector<struct TreeNode *>();
        this->node_name = "Anonymous";
        this->node_type = AST_UNKNOWN;
    }

    explicit TreeNode(const std::string& name, LL_AST_TYPE t) {
        this->parent = nullptr;
        this->children = std::vector<struct TreeNode *>();
        this->node_name = name;
        this->node_type = t;
    }

    explicit TreeNode(const char *name, LL_AST_TYPE t) {
        this->parent = nullptr;
        this->children = std::vector<struct TreeNode *>();
        this->node_name = name;
        this->node_type = t;
    }

    void set_parent(TreeNode *p) {
        this->parent = p;
    }

    void add_child(struct TreeNode *c) {
        if (c != nullptr) {
            this->children.push_back(c);
            c->set_parent(this);
        }
    }

    void set_name(std::string name) {
        this->node_name = std::move(name);
    }

    void set_name(const char *name) {
        this->node_name = name;
    }

    void remove_child(TreeNode *c) {
        if (c != nullptr) {
            std::remove(this->children.begin(), this->children.end(), c);
            c->set_parent(nullptr);
        }
    }

    void print_tree(int depth) {
        std::string result;
        for (int i = 0; i < depth; ++i){
            result += '|';
        }
        result += '[';
        result += std::to_string(this->node_type);
        result += ']';
        result += this->node_name;
        result += '(';
        result += std::to_string(this->children.size());
        result += ')';
        std::cout << result << std::endl;
        for (TreeNode* node: this->children){
            node->print_tree(depth + 1);
        }
    }
} TreeNode;

struct SyntaxTree {
    TreeNode *root;

    void print_tree() const {
        root->print_tree(0);
    }
};


#endif //BAZINGA_COMPILER_SYNTAX_TREE_H
