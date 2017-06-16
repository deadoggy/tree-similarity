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

/// \file zhang_shasha/zhang_shasha_impl.h
///
/// \details
/// Contains the implementation of the Zhang and Shasha algorithm.

#ifndef TREE_SIMILARITY_ZHANG_SHASHA_ZHANG_SHASHA_IMPL_H
#define TREE_SIMILARITY_ZHANG_SHASHA_ZHANG_SHASHA_IMPL_H

template <typename Label, typename CostModel>
void Algorithm<Label, CostModel>::index_nodes_recursion(const node::Node<Label>& node, int& start_postorder, int& start_preorder) {
  // TODO: The call node.label().label() looks little bit odd.
  std::cout << "-- node : " << node.label().label() << std::endl;
  // start_preorder holds this node's preorder id here.
  std::cout << "-- preorder : " << start_preorder << std::endl;
  // Increment start_preorder for the consecutive node in preorder have the
  // correct id.
  start_preorder++;
  // Recursion to childen nodes.
  for (auto child : node.get_children()) {
    index_nodes_recursion(child, start_postorder, start_preorder);
  }
  // start_postorder holds this node's postorder id here.
  std::cout << "-- postorder : " << start_postorder << std::endl;
  // Increment start_postorder for the consecutive node in postorder have the
  // correct id.
  start_postorder++;
}

template <typename Label, typename CostModel>
void Algorithm<Label, CostModel>::index_nodes(const node::Node<Label>& root) {
  std::cout << "--- index_nodes ---" << std::endl;
  int start_postorder = 1;
  int start_preorder = 1;
  index_nodes_recursion(root, start_postorder, start_preorder);
}

template <typename Label, typename CostModel>
double Algorithm<Label, CostModel>::zhang_shasha_ted(const node::Node<Label>& t1, const node::Node<Label>& t2, const CostModel& c) {
  std::cout << "=== zhang_shasha_ted ===" << std::endl;
  index_nodes(t1);
  return 5.0;
}

#endif // TREE_SIMILARITY_ZHANG_SHASHA_ZHANG_SHASHA_IMPL_H