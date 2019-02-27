Readme for OSGridConverter
==========================

Description
-----------

This package allows the user to manipulate co-ordinates on the Earth's surface
in the two major co-ordinate systems: **latitude / longitude** measured in degrees,
and cartographic systems, measured in **eastings and northings**,
based on a local ellipsoidal approximation to the Earth's geoid.

In particular, it provides tools for processing coordinates_
(of the form **AB 12345 12345**) based on the `National Grid`_, defined
by the UK Ordnance Survey.  For more information, see the Ordnance Survey's
National Grid `FAQ page`_.


The package provides basic functions to convert
**latitude / longitude** to the **National Grid** and *vice versa*.  However,
underneath this is a comprehensive system for mapping, and transforming between
different `co-ordinate systems`_, including those for the UK, the Republic of Ireland,
France, North America, and Japan.

Simple Conversion
-----------------

OSGridConverter. **latlong2grid** (*latitude*, *longitude*, *tag* = *'WGS84'*)

  Converts from latitude / longitude to an OS Grid Reference.

    :latitude:
      The latitude of the point, expressed in decimal degrees North

    :longitude:
      The longitude of the point, expressed in decimal degrees East

    :tag:
      The name of the datum used in the conversion; default is *WGS84*,
      referring to the standard datum used by Ordnance Survey

  Return value is an *OSGridReference* object.  For the purpose of simple
  conversions, what matters is that, of *g* is such an object, then *g.E* and
  *g.N* are respectively its easting and northing, expressed in metres, and
  str(g) returns the formatted National Grid reference.

  Example:

  ::

    >>> from OSGridConverter import latlong2grid
    >>> g=latlong2grid(52.657977,1.716038)
    >>> (g.E,g.N)
    (651408, 313177)
    >>> str(g)
    'TG 51408 13177'

OSGridConverter. **grid2latlong** (*grid*, *tag* = *'WGS84'*)

  Converts from an OS Grid Reference to latitude / longitude.

    :grid:
      The point to be converted.  Either an *OSGridReference* object, or a
      string formatted as an Ordnance Survey grid reference,
      e.g. *'TG 51408 13177'*

    :tag:
      The name of the mapping datum used in the conversion; default is *WGS84*,
      referring to the standard datum used by Ordnance Survey

  Return value is a *LatLong* object.  For the purpose of simple
  conversions, what matters is that, of *l* is such an object, then *l.latitude*
  is its latitude expressed oin decimal degrees North, and *g.longitude* is
  its longitude expressed in decimal degrees East.

  Example:

  ::

    >>> from OSGridConverter import grid2latlong
    >>> l=grid2latlong('TG 51408 13177')
    >>> (l.latitude,l.longitude)
    (52.65798005789814, 1.7200761111093394)


OSGridConverter. **Tags**

  A list of strings: names of the standing mapping Data that the package is aware
  of and can convert between.  Its members are the valid values that
  can be used in the *tag* field of the conversion functions.

  ========== ================
  Tag        Details
  ========== ================
  WSG84      UK
  OSGB36     Former UK standard (replaced by WGS84)
  ED50       UK; used for oil and gas exploration
  Irl1975    Republic of Ireland
  NTF        France
  TokyoJapan Japan
  NAD83      North America; very similar to WGS84
  ========== ================

  For more information (and more examples of mapping Data) see the Wikipedia
  page on `Geodetic Datum`_.

**Note**

Conversion from lat / long to grid andthen back to lat / long generally does not
end up with the original values.This is due to a combination of internal rounding
errors, plus the fact thatthe National Grid resolves points to 10m x 10m squares.
In the examples above, the before and after latitudes differ by approx. 1.0e-5
and the longitudes by approx. 3.0e-3; this is typical.


.. _coordinates: https://www.ordnancesurvey.co.uk/docs/support/national-grid-map-references.pdf
.. _`National Grid`: https://www.ordnancesurvey.co.uk/resources/maps-and-geographic-resources/the-national-grid.html
.. _`co-ordinate systems`: https://www.ordnancesurvey.co.uk/docs/support/guide-coordinate-systems-great-britain.pdf
.. _`FAQ page`: https://www.ordnancesurvey.co.uk/support/the-national-grid.html
.. _`Geodetic Datum`: https://en.wikipedia.org/wiki/Geodetic_datum
