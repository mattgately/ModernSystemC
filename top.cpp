/**
 * @file  top.cpp
 * @brief Top-level interconnect implementation
 */
#include "top.hpp"
#include "stimulus.hpp"
#include "duplicator.hpp"
#include "processing.hpp"
#include "checker.hpp"
#include "sc_cxx11.hpp"
using namespace sc_core;

//..............................................................................
Top_module::Top_module( sc_module_name instance ) //< Constructor
{
  /**
   * Instantiate
   */
  stim    = std::make_unique<Stimulus_module>   ( "stim"    );
  dupl    = std::make_unique<Duplicator_module> ( "dupl"    );
  process = std::make_unique<Processing_module> ( "process" );
  check   = std::make_unique<Checker_module>    ( "check"   );
  clock   = std::make_unique<sc_clock>          ( "clock", 10_ns );
  /**
   * Connect
   */
  stim->rawout_port   .bind( raw_fifo         );
  dupl->input_port    .bind( raw_fifo         );
  process->input_port .bind( dupl->out1_xport );
  process->output_port.bind( result_buffer    );
  process->clk_port   .bind( *clock           );
  check->result_port  .bind( result_buffer    );
  check->rawin_port   .bind( dupl->out2_xport );
}

//..............................................................................
Top_module::~Top_module( void ) = default;
