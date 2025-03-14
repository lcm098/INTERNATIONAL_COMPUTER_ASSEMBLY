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
  DD = "DD"
  DL = "DL"
  DR = "DR"
  DA = "DA"

  class << self
    def data_buffer_type
      [RAS_PTR, RAS, RBS, RBS_PTR, RCS, RCS_PTR, RDS, RDS_PTR,
       REX, REX_PTR, DD, DL, DR, DA]
    end
  end
end