#ifndef HSOLVER_H
#define HSOLVER_H

#include "diagh.h"
#include "module_base/macros.h"
#include "module_elecstate/elecstate.h"
#include "module_hamilt_general/hamilt.h"
#include "module_hamilt_pw/hamilt_pwdft/wavefunc.h"
#include "module_hamilt_pw/hamilt_stodft/sto_wf.h"
#include "module_psi/psi.h"

#include <complex>

namespace hsolver
{

template <typename T, typename Device = base_device::DEVICE_CPU>
class HSolver
{
  private:
    using Real = typename GetTypeReal<T>::type;

  public:
    HSolver() {};
    virtual ~HSolver()
    {
        delete pdiagh;
    };
    /*//initialization, used in construct function or restruct a new HSolver
    virtual void init(
        const Basis* pbas //We need Basis class here, use global class for this initialization first
        //const Input &in, //We need new Input class here, use global variable for this initialization first
        //elecstate::ElecState *pes
        )=0;
    //initialization, only be called for change some parameters only
    virtual void update(
        Input &in )=0;*/

    // solve Hamiltonian to electronic density in ElecState
    virtual void solve(hamilt::Hamilt<T, Device>* phm,
                       psi::Psi<T, Device>& ppsi,
                       elecstate::ElecState* pes,
                       const std::string method,
                       const bool skip_charge = false)
    {
        return;
    }

    virtual void solve(hamilt::Hamilt<T, Device>* phm,
                       psi::Psi<T, Device>& ppsi,
                       elecstate::ElecState* pes,
                       const std::string method,

                       const std::string calculation_type_in,
                       const std::string basis_type_in,
                       const bool use_paw_in,
                       const bool use_uspp_in,
                       const int rank_in_pool_in,
                       const int nproc_in_pool_in,

                        const int scf_iter_in,
                        const bool need_subspace_in,
                        const int diag_iter_max_in,
                        const double pw_diag_thr_in,

                       const bool skip_charge)
    {
        return;
    }

    /// @brief solve function for lcao_in_pw
    /// @param phm interface to hamilt
    /// @param ppsi reference to psi
    /// @param pes interface to elecstate
    /// @param transform transformation matrix between lcao and pw
    /// @param skip_charge
    virtual void solve(hamilt::Hamilt<T, Device>* phm,
                       psi::Psi<T, Device>& ppsi,
                       elecstate::ElecState* pes,
                       psi::Psi<T, Device>& transform,
                       const bool skip_charge = false)
    {
        return;
    }
    virtual void solve(hamilt::Hamilt<T, Device>* phm,
                       psi::Psi<T, Device>& ppsi,
                       elecstate::ElecState* pes,
                       ModulePW::PW_Basis_K* wfc_basis,
                       Stochastic_WF& stowf,
                       const int istep,
                       const int iter,
                       const std::string method,

                       const int scf_iter_in,
                       const bool need_subspace_in,
                       const int diag_iter_max_in,
                       const double pw_diag_thr_in,
                       
                       const bool skip_charge)
    {
        return;
    }

    std::string classname = "none";

    // choose method of DiagH for solve Hamiltonian matrix(cg, dav, elpa, scalapack_gvx, cusolver
    std::string method = "none";

    Real diag_ethr = 0.0; // threshold for diagonalization

    // set diag_ethr according to drho (for lcao and lcao-in-pw, we suppose the error is zero and we set diag_ethr to 0)
    virtual Real set_diagethr(Real diag_ethr_in, const int istep, const int iter, const Real drho)
    {
        return 0.0;
    }

    // reset diag_ethr according to drho and hsolver_error
    virtual Real reset_diagethr(std::ofstream& ofs_running, const Real hsover_error, const Real drho, Real diag_ethr_in)
    {
        return 0.0;
    }

    // calculate hsolver_error (for sdft, lcao and lcao-in-pw, we suppose the error is zero)
    virtual Real cal_hsolerror(const Real diag_ethr_in)
    {
        return 0.0;
    };

  protected:
    DiagH<T, Device>* pdiagh = nullptr; // for single Hamiltonian matrix diagonal solver
};

} // namespace hsolver
#endif