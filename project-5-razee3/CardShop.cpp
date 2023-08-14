//Abdullah Razee
//04/04/2023

#include "CardShop.hpp"
#include "Node.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

/**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects
          instantiated with the information read from the file.
    */
CardShop::CardShop(std::string input_file_name)
{
  std::ifstream fin(input_file_name);
  if (fin.fail())
  {
    std::cerr << "File cannot be opened for reading. \n";
    exit(1); // exit if failed to open the file
  }
  // we don't use the first line
  std::string ignore;
  getline(fin, ignore);

  // the columns of the csv associated with the data members
  std::string name, type, race, attribute;
  int level_rank, atk, def;

  std::string temp_string;
  int temp_int;
  int item_counter = 0;
  while (getline(fin, temp_string, ','))
  {
    name = temp_string;

    getline(fin, type, ',');

    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    level_rank = temp_int;

    getline(fin, race, ',');

    getline(fin, attribute, ',');

    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    atk = temp_int;

    getline(fin, temp_string);
    std::istringstream(temp_string) >> temp_int;
    def = temp_int;

    // create new card
    YGOCard *card_ptr = new YGOCard(name, type, level_rank, race, attribute, atk, def);

    // add to linked list and increment counter
    insert(item_counter++, card_ptr);
  }
}

//@post: removes all cards from the shop
// Deallocate and delete items
void CardShop::clear()
{
  for (int i = 0; i < item_count_; i++)
  {
    YGOCard *ptr = getItem(i);
    delete ptr;
    ptr = nullptr;
  }
  DoublyLinkedList::clear();
}

// destructor
CardShop::~CardShop()
{
  clear();
}

//@post: displays information of all cards in the shop, one per line
void CardShop::display()
{
  for (int i = 0; i < item_count_; i++)
  {
    getItem(i)->display();
  }
}

//@param: the index of the first card to be displayed
//@param: the index of the last card to be displayed
//@post: displays the names of all cards in the shop with startRange and endRange,
//       inclusive, one per line
void CardShop::displayName(int startRange, int endRange)
{
  for (int i = startRange; i <= endRange; i++)
  {
    getItem(i)->displayName();
    if (i != endRange)
    {
      std::cout << ", ";
    }
    else
    {
      std::cout << std::endl;
    }
  }
}

//@return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
bool CardShop::operator==(const CardShop &rhs) const
{
  if (getLength() != rhs.getLength())
  {
    return false;
  }
  for (int i = 0; i < getLength(); i++)
  {
    if (*(getPointerTo(i)->getItem()) == *(rhs.getPointerTo(i)->getItem()))
    {
    }
    else
    {
      return false;
    }
  }
  return true;
}

// bubbleSort Function
// Sample code obtained from lecture slide 94 (with some alterations by myself)
// parameters: key sorts by attack or defense and comp for comparison

template <typename Comparator>
int CardShop::bubbleSort(Comparator comp, const std::string &key)
{
  int length = getLength();
  bool isSwap = true;
  int passvalue = 1;
  int countvalue = 0;
  while (isSwap && (passvalue < length))
  {
    isSwap = false;
    for (int index = 0; index < length - passvalue; index++)
    {
      if (key == "atk")
      {
        if (comp(getItem(index + 1)->getAtk(), getItem(index)->getAtk()))
        {
          swap(index + 1, index);
          isSwap = true;
          countvalue++;
        }
      }
      else
      {
        if (comp(getItem(index + 1)->getDef(), getItem(index)->getDef()))
        {
          swap(index + 1, index);
          isSwap = true;
          countvalue++;
        }
      }
    }
    passvalue++;
  }
  return countvalue;
}

// insertionSort
// Sample code obtained from lecture slide 141 (with some alterations by myself)
// parameters: key sorts by attack or defense and comp for comparison

template <typename Comparator>
int CardShop::insertionSort(Comparator comp, const std::string &key)
{
  int length = getLength();
  int countvalue = 0;
  for (int unsorted = 1; unsorted < length; unsorted++)
  {
    int current = unsorted;
    if (key == "atk")
    {
      while ((current > 0) && comp(getItem(current)->getAtk(), getItem(current - 1)->getAtk()))
      {
        swap(current, current - 1);
        current--;
        countvalue++;
      }
    }
    else
    {
      while ((current > 0) && comp(getItem(current)->getDef(), getItem(current - 1)->getDef()))
      {
        swap(current, current - 1);
        current--;
        countvalue++;
      }
    }
  }
  return countvalue;
}

// quickSort function
// parameters: key sorts by attack or defense and comp for comparison

template <typename Comparator>
int CardShop::quickSort(Comparator comp, std::string key)
{
  int length = getLength() - 1;
  int countvalue = 0;
  recursivequicksort(comp, key, 0, length, countvalue);
  return countvalue;
}

// function partitioner
// parameters: key sorts by attack or defense and comp for comparison

template <typename Comparator>
int CardShop::partition(Comparator comp, std::string key, int left, int right, int &countvalue)
{
  int x = left - 1;

  for (int y = left; y <= right; y++)
  {
    if (key == "atk")
    {
      if (comp(getItem(y)->getAtk(), getItem(right)->getAtk()))
      {
        x++;
        swap(x, y);
        countvalue++;
      }
    }
    else
    {
      if (comp(getItem(y)->getDef(), getItem(right)->getDef()))
      {
        x++;
        swap(x, y);
        countvalue++;
      }
    }
  }
  swap(x + 1, right);
  countvalue++;
  return x + 1;
}

// function sorter
// parameters: key sorts by attack or defense and comp for comparison

template <typename Comparator>
void CardShop::recursivequicksort(Comparator comp, std::string key, int left, int right, int &countvalue)
{
  if (left < right)
  {
    int pivot = partition(comp, key, left, right, countvalue);
    recursivequicksort(comp, key, left, pivot - 1, countvalue);
    recursivequicksort(comp, key, pivot + 1, right, countvalue);
  }
}

template <typename Comparator>
int CardShop::mergeSort(Comparator comp, std::string key){
  return -1;
}