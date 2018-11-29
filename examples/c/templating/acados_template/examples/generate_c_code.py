from jinja2 import Environment, FileSystemLoader
from acados_template import *
import acados_template as at
import pkgutil

def export_ode_model():

    model_name = 'pendulum_ode'

    ## Constants
    M = 1
    m = 0.1
    g = 9.81
    l = 0.8

    ## Set up States & Controls
    x1      = SX.sym('x1')
    theta   = SX.sym('theta')
    v1      = SX.sym('v1')
    dtheta  = SX.sym('dtheta')
    
    x = vertcat(x1, v1, theta, dtheta)

    # Controls
    F = SX.sym('F')
    u = vertcat(F)
    
    # xdot
    x1_dot      = SX.sym('x1_dot')
    theta_dot   = SX.sym('theta_dot')
    v1_dot      = SX.sym('v1_dot')
    dtheta_dot  = SX.sym('dtheta_dot')

    xdot = vertcat(x1_dot, theta_dot, v1_dot, dtheta_dot)
    
    ## algebraic variables
    z = []
    
    ## Dynamics     
    denominator = M + m - m*cos(theta)*cos(theta)
    f_expl = vertcat(v1, (-m*l*sin(theta)*dtheta*dtheta + m*g*cos(theta)*sin(theta)+F)/denominator, dtheta, (-m*l*cos(theta)*sin(theta)*dtheta*dtheta + F*cos(theta)+(M+m)*g*sin(theta))/(l*denominator))
    
    f_impl = xdot - f_expl
   
    model = ode_model()

    model.f_impl_expr = f_impl
    model.f_expl_expr = f_expl
    model.x = x
    model.xdot = xdot
    model.u = u
    model.z = z
    model.name = model_name

    return model 

# setting up loader and environment
const1 = ocp_nlp_constant()
import pdb; pdb.set_trace()
acados_path = os.path.dirname(os.path.abspath(at.__file__))
# file_loader = FileSystemLoader(acados_path + '/c_templates')
file_loader = FileSystemLoader('.')
env = Environment(loader = file_loader)
template = env.get_template('template_example.in.c')

# create render arguments
ra = ocp_nlp_render_arguments()

# export model 
model = export_ode_model()

# set model_name 
ra.model_name = model.name

# set ocp_nlp_dimensions
nlp_dims = ra.dims
nx = model.x.size()[0]
nu = model.u.size()[0]
nlp_dims.N  = 100

# set weighting matrices

# set constants
const1 = ocp_nlp_constant()
const1.name  = 'PI'
const1.value = 3.1415926535897932
ra.constants = [const1]

# set QP solver
ra.solver_config.qp_solver = 'PARTIAL_CONDENSING_HPIPM'
ra.solver_config.hessian_approx = 'GAUSS_NEWTON'

# explicit model -- generate C code
generate_c_code_explicit_ode(model);

# render template
output = template.render(ra=ra)

# output file
out_file = open('./c_generated_code/template_example.c', 'w+')
out_file.write(output)

