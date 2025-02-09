#ifndef POTENTIAL_IO_H
#define POTENTIAL_IO_H
#include <string>
#include "module_cell/unitcell.h"
#include "module_basis/module_pw/pw_basis.h"
#include "module_elecstate/module_charge/charge.h"

namespace ModuleIO
{

/// @brief write electric static potential to file
/// @param bz 
/// @param nbz 
/// @param fn 
/// @param rho_basis 
/// @param chr 
/// @param ucell_ 
/// @param v_effective_fixed 
void write_elecstat_pot(
#ifdef __MPI
    const int& bz,
    const int& nbz,
#endif
    const std::string& fn,
    ModulePW::PW_Basis* rho_basis,
    const Charge* const chr,
    const UnitCell* ucell_,
    const double* v_effective_fixed);

} // namespace ModuleIO

#endif // POTENTIAL_IO_H
