class SpecialVariablesAndPointers
  RAS_PTR = "RAS_PTR"
  RAS = "RAS"
  RBS = "RBS"
  RBS_PTR = "RBS_PTR"
  RCS = "RCS"
  RCS_PTR = "RCS_PTR"
  RDS = "RDS"
  RDS_PTR = "RDS_PTR"
  REX = "REX"
  REX_PTR = "REX_PTR"
  ECX_RES = "ECX_RES" # used to resolve value at address
  EDX_RES = "EDX_RES" # used to resolve value at address
  EEX_RES = "EEX_RES" # used to resolve value at address
  EFX_RES = "EFX_RES" # used to resolve value at address
  EGX_RES = "EGX_RES" # used to resolve value at address
  EHX_RES = "EHX_RES" # used to resolve value at address

  DD = "DD"
  DL = "DL"
  DR = "DR"
  DA = "DA"

  class << self
    def data_buffer_type
      [RAS_PTR, RAS, RBS, RBS_PTR, RCS, RCS_PTR, RDS, RDS_PTR,
       REX, REX_PTR, DD, DL, DR, DA, ECX_RES, EDX_RES, EEX_RES, 
      EFX_RES, EGX_RES, EHX_RES]
    end
  end
end