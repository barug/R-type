//
// MyMonster.hpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Dec 13 19:33:48 2016 Thomas Billot
// Last update Fri Dec 23 18:42:40 2016 Thomas Billot
//

#pragma once

# include	<vector>
# include	<memory>
# include	<string>
# include	<iostream>
# include	"../includes/EntityManager.hpp"
# include	"../includes/SystemManager.hpp"
# include       "../includes/Components.hpp"

typedef int (*ptrToF)(EntityManager &e, SystemManager &s);

extern	"C"
{
  ptrToF	returnLoader();
}
