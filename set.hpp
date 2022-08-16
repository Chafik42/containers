/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:51:12 by cmarouf           #+#    #+#             */
/*   Updated: 2022/08/16 19:36:07 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_CPP
# define SET_CPP

# include <iostream>
# include <memory>

# include "utils/pair.hpp"
# include "utils/make_pair.hpp"
# include "utils/is_integral.hpp"
# include "utils/lexicographical_compare.hpp"
# include "utils/equal.hpp"
# include "utils/enable_if.hpp"
# include "iterators/iterator_traits.hpp"
# include "iterators/bidirectional_iterator.hpp"
# include "iterators/SET_RBT_iterator.hpp"
# include "iterators/reverse_iterator.hpp"
# include "utils/SET_red_black_tree.hpp"

namespace ft
{
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> > 
	class set
	{
		public:
			typedef T 															key_type;
			typedef T   														mapped_type;
			typedef T	   														value_type;
			typedef Compare 													key_compare;
			typedef Compare 													value_compare;
			typedef Alloc														allocator_type;
			typedef typename    allocator_type::difference_type 				difference_type;
			typedef typename    allocator_type::size_type 						size_type;
			typedef typename    allocator_type::reference 						reference;
			typedef typename    allocator_type::const_reference 				const_reference;
			typedef typename    allocator_type::pointer 						pointer;
			typedef typename    allocator_type::const_pointer 					const_pointer;
			typedef typename    ft::RBT<value_type, Compare>::iterator 			iterator;
			typedef typename    ft::RBT<value_type, Compare>::const_iterator 	const_iterator;
			typedef typename    ft::reverse_iterator<iterator> 					reverse_iterator;
			typedef typename    ft::reverse_iterator<const_iterator> 			const_reverse_iterator;

			//** Constructors / Destructor

			//* Empty Constructor
			explicit set( const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type() ) : _size(0), _cmp(comp), _alloc(alloc)
			{
				
			}

			//* Range Constructor
			template < class InputIterator >
			set( InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() ) : _size(0), _cmp(comp), _alloc(alloc)
			{
				while ( first != last )
				{
					insert(*first);
					first++;
				}
			}

			//* Copy Constructor
			set( const set & x ) : _size(0)
			{
				*this = x;
			}

			//* Destructor
			~set( void )
			{
				_root.clear();	
			}
			
			//* Operator =
			set & operator=( const set & x )
			{
				if ( *this != x )
				{
					_cmp = x._cmp;
					_alloc = x._alloc;
					_root.clear();
					insert(x.begin(), x.end());
					_size = x._size;
				}
				return *this;
			}

			//** Iterators

			iterator begin( void )
			{
				return _root.begin();
			}
			
			const_iterator begin( void ) const
			{
				return _root.const_begin();
			}

			iterator end( void )
			{
				return _root.end();	
			}

			const_iterator end( void ) const
			{
				return _root.const_end();	
			}

			//* Reverse Iterators

			reverse_iterator rbegin( void )
			{
				return reverse_iterator(_root.end());
			}
			
			const_reverse_iterator rbegin( void ) const
			{
				return const_reverse_iterator(_root.const_end());
			}

			reverse_iterator rend( void )
			{
				return reverse_iterator(_root.begin());
			}

			const_reverse_iterator rend( void ) const
			{
				return const_reverse_iterator(_root.const_begin());	
			}


			//* Capacity

			//* Empty
			bool empty( void ) const
			{
				return _size == 0;
			}

			//* Size
			size_type size( void ) const
			{
				return _size;
			}
			
			//* Max_size
			size_type max_size( void ) const
			{
				return _root.max_size();
			}
			
			//** Modifiers

			//* Single element Insert
			ft::pair<iterator,bool> insert( const value_type & val )
			{
				ft::pair<iterator,bool> ret = _root.insert(val);
				if ( ret.second )
					_size++;
				return ret;
			}
			
			//* Single element Insert with hint
			iterator insert( iterator position, const value_type & val )
			{(void) position;
				return insert(val).first;
			}

			//* Range Insert
			template <class InputIterator>
  			void insert ( InputIterator first, InputIterator last )
			{
				while ( first != last )
				{
					insert(*first);
					first++;
				}
			}
			
			//* Erase with position
			void erase( iterator position )
			{
				erase(*position);
			}

			//* Erase with value
			size_type erase( const value_type & val )
			{
				ft::pair<iterator,bool> ret = _root.erase(val);
				if ( ret.second == true )
				{
					_size--;
					return 1;
				}
				return 0;
			}

			//* Range Erase
			void erase( iterator first, iterator last )
			{
				iterator tmp;
				while ( first != last )
				{
					tmp = first;
					first++;
					erase(*tmp);
				}
			}

			//* Swap
			void swap( set & x )
			{
				size_type       			_size_tmp = _size;
				key_compare    	     		_cmp_tmp = _cmp;
				allocator_type  			_alloc_tmp = _alloc;

				_size = x._size;
				_cmp = x._cmp;
				_alloc = x._alloc;

				x._size = _size_tmp;
				x._cmp = _cmp_tmp;
				x._alloc = _alloc_tmp;
				_root.swap(x._root);
			}

			//* Clear
			void clear( void )
			{
				_root.clear();
				_size = 0;
			}

			//** Observers

			//* Key_comp
			key_compare key_comp( void ) const
			{
				return _cmp;
			}

			//* Value_comp
			value_compare value_comp( void ) const
			{
				return value_compare(_cmp);
			}

			//** Operations
			
			//* Find
			iterator find( const value_type & val )
			{
				return _root.find(val);
			}

			const_iterator find( const value_type & val ) const
			{
				return _root.find(val);
			}

			//* Count
			size_type count( const value_type & val ) const
			{
				return _root.count(val);
			}

			//* Lower_bound
			iterator lower_bound( const value_type & val )
			{
				return _root.lower_bound(val);
			}

			const_iterator lower_bound( const value_type & val ) const
			{
				return _root.lower_bound(val);
			}

			// //* Upper_bound
			iterator upper_bound( const value_type & val )
			{
				return _root.upper_bound(val);
			}

			const_iterator upper_bound( const value_type & val ) const
			{
				return _root.upper_bound(val);
			}

			//* Equal_range
			pair<iterator,iterator> equal_range( const value_type & val )
			{
				return ft::make_pair<iterator, iterator>(lower_bound(val), upper_bound(val));
			}

			pair<const_iterator,const_iterator> equal_range( const value_type & val ) const
			{
				return ft::make_pair<const_iterator, const_iterator>(lower_bound(val), upper_bound(val));
			}

			//* Allocator

			//* allocator_getter
			allocator_type get_allocator( void ) const
			{
				return _alloc;
			}

		private:
			RBT<value_type, key_compare> _root;
			size_type       _size;
			key_compare     _cmp;
			allocator_type  _alloc;
		
	};

	template < class T, class Compare, class Alloc >
  	void swap( set<T,Compare,Alloc> & x, set<T,Compare,Alloc> & y )
	{
		if ( x == y )
			return ;
		x.swap(y);
	}

	template < class T, class Compare, class Alloc >
	bool operator==( const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs )
	{
		if ( lhs.size() != rhs.size() )
			return false;
		typename set<T, Compare, Alloc>::const_iterator it = lhs.begin();
		typename set<T, Compare, Alloc>::const_iterator ite = lhs.end();
		typename set<T, Compare, Alloc>::const_iterator rit = rhs.begin();
		
		while ( it != ite && rit != rhs.end() )
		{
			if ( *it != *rit || *it != *rit )
				return false;
			it++;
			rit++;
		}
		if ( it != ite || rit != rhs.end() )
			return false;
		return true;
	}

	template < class T, class Compare, class Alloc >
	bool operator!=( const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs )
	{
		return !(lhs == rhs);
	}

	template < class T, class Compare, class Alloc >
  	bool operator<( const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}	

	template < class T, class Compare, class Alloc >
  	bool operator<=( const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs )
	{
		return !(rhs < lhs);
	}
	
	template < class T, class Compare, class Alloc >
  	bool operator>( const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs )
	{
		return rhs < lhs;
	}

	template < class T, class Compare, class Alloc >
  	bool operator>=( const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs )
	{
		return !(lhs < rhs);
	}
}

#endif