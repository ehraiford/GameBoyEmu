import inspect

class FunctionError(Exception):
    def __init__(self):
        frame = inspect.currentframe().f_back  # Get the caller's frame
        func_name = frame.f_code.co_name       # Get the function name
        args, _, _, values = inspect.getargvalues(frame)  # Get function arguments
        
        arg_str = ", ".join(f"{arg}={values[arg]!r}" for arg in args)  # Format arguments
        message = f"Error in {func_name}({arg_str})"
        
        super().__init__(message)


for i in range(0, 512):
    pass




def get_r8(val: int) -> str:
    if val == 0:
        return "cpu->get_b_pointer()"
    elif val == 1:
        return "cpu->get_c_pointer()"
    elif val == 2:
        return "cpu->get_d_pointer()"
    elif val == 3:
        return "cpu->get_e_pointer()"
    elif val == 4:
        return "cpu->get_h_pointer()"
    elif val == 5:
        return "cpu->get_l_pointer()"
    elif val == 6:
        return "TODO"
    elif val == 7:
        return "cpu->get_a_pointer()"
    else:
        raise FunctionError()
    
def get_r16(val: int) -> str:
    if val == 0:
        return "cpu->get_bc_pointer()"
    elif val == 1:
        return "cpu->get_de_pointer()"
    if val == 2:
        return "cpu->get_hl_pointer()"
    elif val == 3:
        return "cpu->get_sp_pointer()"
    else:
        raise FunctionError()
    
def get_r16stk(val: int) -> str:
    if val == 0:
        return "cpu->get_bc_pointer()"
    elif val == 1:
        return "cpu->get_de_pointer()"
    if val == 2:
        return "cpu->get_hl_pointer()"
    elif val == 3:
        return "cpu->get_af_pointer()"
    else:
        raise FunctionError()
            
        