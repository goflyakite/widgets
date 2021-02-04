#include <eosio/eosio.hpp>

using namespace eosio;
using namespace std;

// class [[eosio::conytract]] 
CONTRACT widgets : public contract {
  public:

    using contract::contract;

    TABLE widget {
      uint64_t id = 0;
      uint64_t quantity;
      string widgetname;
      string widgetdescrip;
      name owner = name( "widgetboss" );

      auto primary_key() const { return id; };
    };
    typedef multi_index<name("widgetshelf"), widget> widgetshelf_table;

    ACTION addwidget( int128_t id, string widgetname, string widgetdescrip, uint64_t quantity) {
     
      check( has_auth( name ( "widgetsboss") ), "You're not my daddy.");

      widgetshelf_table _widgetshelf( get_self(),  get_self().value);     // Pass in Code (this  contract) and Scope

      // Add new widget if it doesn't exist, otherwise increase quantity.
      if ( id == -1 ) {
        _widgetshelf.emplace( get_self(), [&](auto& new_widget_row) {
          new_widget_row.id = _widgetshelf.available_primary_key();
          new_widget_row.widgetname = widgetname;
          new_widget_row.widgetdescrip = widgetdescrip;
          new_widget_row.quantity = quantity;
        });
      } else {
        // Increase quantity if we find widget. Does not change name.
        auto itr = _widgetshelf.find(id);
        check( itr != _widgetshelf.end(), "\nWidget not found.");

        _widgetshelf.modify(itr, get_self(), [&]( auto& row_to_modify ) {
          row_to_modify.quantity += quantity; 
        });
      }
      print ("Success!");
    }

    ACTION onlyboss() {
      require_auth( name ( "widgetsboss") );
      print ("Only user widgetsboss is allowed here. Hello BOSS.");
    }

    ACTION goodbye( name leaving) { 
      print ("Goodbye cruel world...", leaving);
    }

};