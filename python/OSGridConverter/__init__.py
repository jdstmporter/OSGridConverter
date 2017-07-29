from .grid import OSGridReference
from .latlong import LatLong
from .mapping import Tags

def latlong2grid(latitude,longitude,tag='WGS84'):
    ll=LatLong(latitude,longitude,tag=tag)
    return OSGridReference(ll)
    
def grid2latlong(grid,tag='WGS84'):
    gr=OSGridReference(grid)
    return gr.toLatLong(tag=tag)

