import vtk
import numpy as np
from math import sqrt 
from math import pow

def switchVTK():
  print"start Mapper"

  ctx.field("outAorticCenterlineMarker.deleteAll").touch()


  print"end Mapper"