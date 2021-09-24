#pragma once

#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <stdexcept>
#include <vector>

#include "delaunator.hpp"


std::vector<double> concavehull(const std::vector<double>& coords, double chi_factor=0.1) {

	if (chi_factor < 0 || chi_factor > 1) {
		throw std::invalid_argument("Chi factor must be between 0 and 1 inclusive");
	}

	delaunator::Delaunator d(coords);

	// Determine initial points on outside hull
	std::vector<size_t> bpoints = d.get_hull_points();
	std::set<size_t> bset(bpoints.begin(), bpoints.end());

	// Make max heap of boundary edges with lengths
	typedef std::pair<size_t, double> hpair;
	
	auto cmp = [](hpair left, hpair right) {
			   return left.second < right.second;
		   };
	
	std::vector<hpair> bheap(bpoints.size());

	double max_len = std::numeric_limits<double>::min();
	double min_len = std::numeric_limits<double>::max();
	
	for (auto point : bpoints) {
		size_t e = d.hull_tri[point];
		double len = d.edge_length(e);

		bheap.push_back({e, len});
		std::push_heap(bheap.begin(), bheap.end(), cmp);

		min_len = std::min(len, min_len);
		max_len = std::max(len, max_len);
	}

	// Determine length parameter
	double length_param = chi_factor * max_len + (1 - chi_factor) * min_len;

	// Iteratively add points to boundary by iterating over the triangles on the hull
	while (!bheap.empty()) {

		// Get edge with the largest length
		std::pop_heap(bheap.begin(), bheap.end(), cmp);
		const auto [e, len] = bheap.back();
		bheap.pop_back();

		// Length of edge too small for our chi factor
		if (len <= length_param) {
			break;
		}

		// Find interior point given edge e (a -> b)
		//       e
		//  b <----- a
		//     \   /
		//  e_b \ / e_a
		//       c
		size_t c = d.get_interior_point(e);

		// Point already belongs to boundary
		if (bset.count(c)) {
			continue;
		}

		// Get two edges connected to interior point
		//  c -> b
		size_t e_b = d.halfedges[delaunator::next_halfedge(e)];
		//  a -> c
		size_t e_a = d.halfedges[delaunator::next_halfedge(delaunator::next_halfedge(e))];

		// Add edges to heap
		double len_a = d.edge_length(e_a);
		double len_b = d.edge_length(e_b);

		bheap.push_back({e_a, len_a});
		std::push_heap(bheap.begin(), bheap.end(), cmp);
		bheap.push_back({e_b, len_b});
		std::push_heap(bheap.begin(), bheap.end(), cmp);
		
		// Update outer hull and connect new edges
		size_t a = d.triangles[e];
		size_t b = d.triangles[delaunator::next_halfedge(e)];

		d.hull_next[c] = b;
		d.hull_prev[c] = a;
		d.hull_next[a] = d.hull_prev[b] = c;
		
		bset.insert(c);	
	}

	return d.get_hull_coords();
}

