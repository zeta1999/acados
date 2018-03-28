/*
 *    This file is part of acados.
 *
 *    acados is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    acados is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with acados; if not, write to the Free Software Foundation,
 *    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef ACADOS_OCP_NLP_OCP_NLP_SQP_H_
#define ACADOS_OCP_NLP_OCP_NLP_SQP_H_

#ifdef __cplusplus
extern "C" {
#endif

// acados_c
// #include <acados_c/ocp_qp_interface.h>
// #include <acados_c/sim.h>

// acados
#include "acados/ocp_nlp/ocp_nlp_common.h"
#include "acados/sim/sim_collocation_utils.h" // TODO remove ???
#include "acados/sim/sim_common.h"
#include "acados/utils/types.h"
// blasfeo
#include "blasfeo/include/blasfeo_target.h"
#include "blasfeo/include/blasfeo_common.h"



/************************************************
* options
************************************************/

typedef struct
{
    int maxIter;
	double min_res_g;
	double min_res_b;
	double min_res_d;
	double min_res_m;
    void *qp_solver_opts;
	void **dynamics; // dynamics_opts
	void **cost; // cost_opts
	void **constraints; // constraints_opts
} ocp_nlp_sqp_opts;

//
int ocp_nlp_sqp_opts_calculate_size(void *config, ocp_nlp_dims *dims);
//
void *ocp_nlp_sqp_opts_assign(void *config, ocp_nlp_dims *dims, void *raw_memory);
//
void ocp_nlp_sqp_opts_initialize_default(void *config, ocp_nlp_dims *dims, void *opts);
//
void ocp_nlp_sqp_opts_update(void *config, ocp_nlp_dims *dims, void *opts);



/************************************************
* memory
************************************************/

typedef struct
{
//    ocp_nlp_dims *dims;
    void *qp_solver_mem;

    void **dynamics; // dynamics memory
	void **cost; // cost memory
	void **constraints; // constraints memory

    // residuals
	ocp_nlp_res *nlp_res;

	// nlp memory
	ocp_nlp_memory *nlp_mem;

	int sqp_iter;
	int dummy;  // NOTE(dimitris): make struct size multiple of 8
} ocp_nlp_sqp_memory;

//
int ocp_nlp_sqp_memory_calculate_size(void *config, ocp_nlp_dims *dims, void *opts_);
//
void *ocp_nlp_sqp_memory_assign(void *config, ocp_nlp_dims *dims, void *opts_, void *raw_memory);



/************************************************
* workspace
************************************************/

typedef struct
{

    // QP solver
    ocp_qp_in *qp_in;
    ocp_qp_out *qp_out;
    void *qp_work;

    void **dynamics; // dynamics_workspace
    void **cost; // cost_workspace
    void **constraints; // constraints_workspace

} ocp_nlp_sqp_work;

//
int ocp_nlp_sqp_workspace_calculate_size(void *config, ocp_nlp_dims *dims, void *opts_);



/************************************************
* functions
************************************************/

//
int ocp_nlp_sqp(void *config, ocp_nlp_dims *dims, ocp_nlp_in *nlp_in, ocp_nlp_out *nlp_out, void *args, void *mem, void *work_);
//
void ocp_nlp_sqp_config_initialize_default(void *config_);



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  // ACADOS_OCP_NLP_OCP_NLP_SQP_H_
