/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 21:57:26 by cmarouf           #+#    #+#             */
/*   Updated: 2022/08/08 15:02:43 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#   define PAIR_HPP

namespace ft
{
    template <class T1, class T2>
    struct pair
    {
        //* Members type
        typedef T1 first_type;
        typedef T2 second_type;


        //* Members variable
        first_type  first;
        second_type second;

        //* Constructor
        pair( void )
        {
            
        }

        template<class U, class V>
        pair( const pair<U,V> & pr ) : first(pr.first), second(pr.second)
        {
            *this = pr;
        }

        pair( const first_type & a, const second_type & b ) : first(a), second(b)
        {
            
        }

        //* Operator =
        pair & operator=( const pair & pr )
        {
            first = pr.first;
            second = pr.second;
            return *this;
        }
    };
    
    template <class T1, class T2>
    bool operator==( const pair<T1,T2> & lhs, const pair<T1,T2> & rhs )
    {
        return (lhs.first == rhs.first) && (lhs.second == rhs.second);
    }

    template <class T1, class T2>
    bool operator!=( const pair<T1,T2> & lhs, const pair<T1,T2> & rhs )
    {
        return !(lhs == rhs);
    }

    template <class T1, class T2>
    bool operator<( const pair<T1,T2> & lhs, const pair<T1,T2> & rhs )
    {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template <class T1, class T2>
    bool operator<=( const pair<T1,T2> & lhs, const pair<T1,T2> & rhs )
    {
        return !(rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>( const pair<T1,T2> & lhs, const pair<T1,T2> & rhs )
    {
        return rhs < lhs;
    }

    template <class T1, class T2>
    bool operator>=( const pair<T1,T2> & lhs, const pair<T1,T2> & rhs )
    {
        return !(lhs < rhs);
    }
}

#endif