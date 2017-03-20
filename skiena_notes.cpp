# Geomtry
typedef struct {
        double a; /* x-coefficient */
        double b; /* y-coefficient */
        double c; /* constant term */
} line;

points_to_line(point p1, point p2, line *l)
{
        if (p1[X] == p2[X]) {
                l->a = 1;
                l->b = 0;
                l->c = -p1[X];
        } else {
                l->b = 1;
                l->a = -(p1[Y]-p2[Y])/(p1[X]-p2[X]);
                l->c = -(l->a * p1[X]) - (l->b * p1[Y]);
        } 
}
point_and_slope_to_line(point p, double m, line *l)
{
        l->a = -m;
        l->b = 1;
        l->c = -((l->a*p[X]) + (l->b*p[Y]));
}

bool parallelQ(line l1, line l2)
{
     return ( (fabs(l1.a-l2.a) <= EPSILON) &&
              (fabs(l1.b-l2.b) <= EPSILON) );
}
bool same_lineQ(line l1, line l2)
{
     return ( parallelQ(l1,l2) && (fabs(l1.c-l2.c) <= EPSILON) );
}

intersection_point(line l1, line l2, point p)
{
     if (same_lineQ(l1,l2)) {
         printf("Warning: Identical lines, all points intersect.\n");
         p[X] = p[Y] = 0.0;
         return;
     }
     if (parallelQ(l1,l2) == TRUE) {
         printf("Error: Distinct parallel lines do not intersect.\n");
         return;
     }
     p[X] = (l2.b*l1.c - l1.b*l2.c) / (l2.a*l1.b - l1.a*l2.b);
     if (fabs(l1.b) > EPSILON)       /* test for vertical line */
             p[Y] = - (l1.a * (p[X]) + l1.c) / l1.b;
     else
             p[Y] = - (l2.a * (p[X]) + l2.c) / l2.b;
}
      
      
Angles between lines
tanθ = a1b2 −a2b1 / a1a2 + b1b2
tanθ = (m2 − m1)/(m1m2 + 1)

closest_point(point p_in, line l, point p_c){
  line perp;              /* perpendicular to l through (x,y) */
  
  if (fabs(l.b) <= EPSILON) { // verticle line
        p_c[X] = -(l.c);
        p_c[Y] = p_in[Y];
        return;
  }
  if (fabs(l.a) <= EPSILON) {// horizontal line
        p_c[X] = p_in[X];
        p_c[Y] = -(l.c);
        return;
  }
  point_and_slope_to_line(p_in,1/l.a,&perp); /* normal case */
  intersection_point(l,perp,p_c);
}
