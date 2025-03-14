class SpecialVariablesAndPointers

  # General Special Variable
  RAS_PTR = "ras_ptr"
  RAS = "ras"
  RBS = "rbs"
  RBS_PTR = "rbs_ptr"
  RCS = "rcs"
  RCS_PTR = "rcs_ptr"
  RDS = "rds"
  RDS_PTR = "rds_ptr"
  REX = "rex"
  REX_PTR = "rex_ptr"

  ECX_RES = "ecx_res" # used to resolve value at address
  EDX_RES = "edx_rex" # used to resolve value at address
  EEX_RES = "eex_res" # used to resolve value at address
  EFX_RES = "efx_res" # used to resolve value at address
  EGX_RES = "egx_rex" # used to resolve value at address
  EHX_RES = "ehx_rex" # used to resolve value at address

  # pointer variable
  FPTR = "fptr"
  VPTR = "vptr"

  # track variable
  RDO_VAR = "rdo_var"

  # FOR CREATING LIST, ARRAY, DICT, RAW VARIABLE
  DD = "dd"
  DL = "dl"
  DR = "dr"
  DA = "da"

  class << self
    def data_buffer_type
      [RAS_PTR, RAS, RBS, RBS_PTR, RCS, RCS_PTR, RDS, RDS_PTR,
       REX, REX_PTR, DD, DL, DR, DA, ECX_RES, EDX_RES, EEX_RES, 
      EFX_RES, EGX_RES, EHX_RES, RDO_VAR, FPTR, VPTR]
    end
  end
end