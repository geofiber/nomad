#ifndef _NOMADSTDCINTERFACE_H_
#define _NOMADSTDCINTERFACE_H_

// strongly inspired by Ipopt C interface

#ifdef __cplusplus
extern "C"
{
#endif

    // Contains the most important things to solve a Nomad problem
    struct NomadProblemInfo;

    // Pointer to a Nomad problem
    typedef struct NomadProblemInfo *NomadProblem;

    // To pass other informations required in the blackbox (can be useful for other interfaces)
    typedef void *NomadUserDataPtr;

    // Blackbox functions types (TODO add for blackbox block evaluation functions functions ?)
    typedef bool (*Callback_BB_single)(int, double *, int, double *, NomadUserDataPtr);
    
    // TODO add blackbox output types ?

    // TODO find a way to have stop reason

    NomadProblem createNomadProblem(
        Callback_BB_single bb_single, // black box function
        int nb_inputs,                // number of inputs
        int nb_outputs,               // number of outputs
        double *x_lb,                 // lower bounds (can be null)
        double *x_ub,                 // upper bounds (can be null)
        char *type_bb_outputs,        // follow the conventions of Nomad.
        int max_bb_eval               // maximum number of evaluations allowed
    );

    void freeNomadProblem(NomadProblem nomad_problem);

    // Display parameters
    bool addNomadBoolDispParam(NomadProblem nomad_problem,
                               char *keyword,
                               bool flag);

    bool addNomadValDispParam(NomadProblem nomad_problem,
                              char *keyword,
                              int flag);

    bool addNomadStringDispParam(NomadProblem nomad_problem,
                                 char *keyword,
                                 char *param_str);

    // Run parameters
    bool addNomadBoolRunParam(NomadProblem nomad_problem,
                              char *keyword,
                              bool flag);

    // Add other methods according to preferences (to discuss with Christophe and Viviane)

    // TODO precise a return status; allow the evaluations of several points
    // For the moment, do not allow the warm start
    bool solveNomadProblem(NomadProblem nomad_problem,
                          double *x0,                      // starting point
                          bool *exists_feas_sol,            // indicates if the algorithm finds a feasible solution
                          double *bb_best_x_feas,          // At the end, contains feas solution if this last one exists
                          double *bb_best_feas_outputs,    // At the end, contains feas output solution if this last one exists
                          bool *exists_inf_sol,             // Indicates if the algorithm finds an infeasible solution
                          double *bb_best_x_inf,           // At the end, contains infeas input solution if this last one exists
                          double *bb_best_inf_outputs,     // At the end, contains infeas output solution if this last one exists
                          NomadUserDataPtr user_data_ptr); // Anything, responsability is on you

#ifdef __cplusplus
}
#endif
#endif /* ifndef SYMBOL */
