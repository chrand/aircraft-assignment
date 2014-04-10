#include<iostream>
#include<cctype>
#include<iomanip>
#include<stdio.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/python.hpp>

using namespace std;
using namespace boost::numeric::ublas;

#define ROWS_CLASS_FIRST_BEGIN 1
#define ROWS_CLASS_FIRST_END   2
#define ROWS_CLASS_BUSINESS_BEGIN 3
#define ROWS_CLASS_BUSINESS_END   7
#define ROWS_CLASS_ECONOMY_BEGIN 8
#define ROWS_CLASS_ECONOMY_END   13

#define SEATS_PER_ROW 6
#define ROWS_TOTAL ROWS_CLASS_ECONOMY_END


// TODO: first,business,economy: restrict to assigned rows

//flow
/*
loop
print schema
get input
is q? exit
parse input
validate parsed input
if valid:
  if seat is free: change global state
  else: notify not free
else: notify not valid
*/
// class
// aircraft seats: 2d array of bits
// initialize: all empty
// is_free()?
// occupy()
// print()

char const* greet(){
   return "hello, world";
}

class Aircraft {
private:
  unsigned int rows_total;
  unsigned int rows_class_first_begin;
  unsigned int rows_class_first_end;
  unsigned int rows_class_business_begin;
  unsigned int rows_class_business_end;
  unsigned int rows_class_economy_begin;
  unsigned int rows_class_economy_end;
  unsigned int seats_per_row;
  // aircraft holders
  matrix<bool> seats_map;
public:
  // constructor
  Aircraft(
      unsigned int rows_class_first_begin=ROWS_CLASS_FIRST_BEGIN,
      unsigned int rows_class_first_end=ROWS_CLASS_FIRST_END,
      unsigned int rows_class_business_begin=ROWS_CLASS_BUSINESS_BEGIN,
      unsigned int rows_class_business_end=ROWS_CLASS_BUSINESS_END,
      unsigned int rows_class_economy_begin=ROWS_CLASS_ECONOMY_BEGIN,
      unsigned int rows_class_economy_end=ROWS_CLASS_ECONOMY_END,
      unsigned int seats_per_row=SEATS_PER_ROW
    ) {
    this->rows_class_first_begin=rows_class_first_begin;
    this->rows_class_first_end=rows_class_first_end;
    this->rows_class_business_begin=rows_class_business_begin;
    this->rows_class_business_end=rows_class_business_end;
    this->rows_class_economy_begin=rows_class_economy_begin;
    this->rows_class_economy_end=rows_class_economy_end;
    this->seats_per_row=seats_per_row;
    this->rows_total=rows_class_economy_end;
    //
    this->seats_map.resize(rows_total,seats_per_row);
    this->empty();
  }
  /*--------------------------------------------------------*/
  void empty() {
    for (unsigned int row=0; row<this->rows_total; row++) {
      for (unsigned int seat=0; seat<this->seats_per_row; seat++) {
        this->seats_map (row,seat) = false;
      }
    }
  }
  /*--------------------------------------------------------*/
  void show() {
    for (unsigned int row=0; row<seats_map.size1 (); row++) {
      printf("row: %2d   ",row);
      for (unsigned int seat=0; seat<seats_map.size2 (); seat++) {
        // element
        if (seats_map (row,seat)==true) { printf("X"); }
        else { printf("-"); }
        // separator
        if (2*(seat+1)==seats_per_row) { printf("  "); }
      }
      printf("\n");
    }
  }
  /*--------------------------------------------------------*/
  bool seat_is_free(unsigned int row, unsigned int seat) {
    return seats_map (row,seat)==false;
  }
  /*--------------------------------------------------------*/
  unsigned int seat_occupy(unsigned int row, unsigned int seat) {
    if ( (row>=seats_map.size1()) || (seat>=seats_map.size2()) ) {
      fprintf(stderr,"# warning: (row:%d,seat:%d) exceeds capacity\n",row,seat);
      return 1;
    }
    else if (! seat_is_free(row,seat)) {
      fprintf(stderr,"# warning: (row:%d,seat:%d) already occupied\n",row,seat);
      return 2;
    }
    else {
      seats_map (row,seat)=true;
    }
    return 0;
  }
  /*--------------------------------------------------------*/
};

int main() {
  Aircraft aircraft=Aircraft();
  aircraft.seat_occupy(0,0);
  aircraft.seat_occupy(0,0);
  aircraft.seat_occupy(90,90);
  aircraft.show();
  return 0;
}

BOOST_PYTHON_MODULE(seat_booking) {
  using namespace boost::python;
  def("greet", greet);
  class_<Aircraft>("Aircraft", init<unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int>())
    .def("empty", &Aircraft::empty)
    .def("show", &Aircraft::show)
    .def("seat_is_free", &Aircraft::seat_is_free)
    .def("seat_occupy", &Aircraft::seat_occupy)
    ;
}
