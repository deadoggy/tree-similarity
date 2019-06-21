// The MIT License (MIT)
// Copyright (c) 2017 Mateusz Pawlik, Nikolaus Augsten, and Daniel Kocher.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

/// \file node/tree_indexer_impl.h
///
/// \details
/// Contains the implementation of tree indexes.

#ifndef TREE_SIMILARITY_NODE_TREE_INDEXER_IMPL_H
#define TREE_SIMILARITY_NODE_TREE_INDEXER_IMPL_H

template <typename TreeIndex, typename Label>
void index_tree(TreeIndex& ti, const node::Node<Label>& n,
    label::LabelDictionary<Label> ld) {
  
  unsigned int tree_size = n.get_tree_size();
  
  if constexpr (std::is_base_of<PostLToSize, TreeIndex>::value) {
    ti.postl_to_size_.resize(tree_size);
  }
  if constexpr (std::is_base_of<PostLToLabelId, TreeIndex>::value) {
    ti.postl_to_label_id_.resize(tree_size);
  }
  
  // Orders start with '0'.
  unsigned int start_preorder = 0;
  unsigned int start_postorder = 0;
  index_tree_recursion(ti, n, ld, start_preorder, start_postorder);
  
};

template <typename TreeIndex, typename Label>
unsigned int index_tree_recursion(TreeIndex& ti, const node::Node<Label>& n,
    label::LabelDictionary<Label> ld, unsigned int& start_preorder,
    unsigned int& start_postorder) {
  
  // Stores number of descendants of this node. Incrementally computed while
  // traversing the children.
  unsigned int desc_sum = 0;

  // Here, start_preorder holds this node's preorder id.

  // Increment start_preorder to hold the correct id of the consecutive node
  // in preorder.
  ++start_preorder;

  // Recursions to childen nodes.
  auto children_start_it = std::begin(n.get_children());
  auto children_end_it = std::end(n.get_children());
  while (children_start_it != children_end_it) {
    desc_sum += index_tree_recursion(ti, *children_start_it, ld, start_preorder, start_postorder);
    // Continue to consecutive children.
    ++children_start_it;
  }

  // Here, start_postorder holds this node's postorder id.
  
  if constexpr (std::is_base_of<PostLToSize, TreeIndex>::value) {
    if (n.is_leaf()) {
      // Leaf has size 1.
      ti.postl_to_size_[start_postorder] = 1;
    } else {
      // Inner node has size desc_sum+1.
      ti.postl_to_size_[start_postorder] = desc_sum + 1;
    }
  }

  // Increment start_postorder for the consecutive node in postorder to have the
  // correct id.
  ++start_postorder;

  // Return the number of nodes in the subtree rooted at this node.
  return desc_sum + 1;
  
};

#endif // TREE_SIMILARITY_NODE_TREE_INDEXER_IMPL_H