#include "Edge.h"
#include "Loop.h"
#include <type_traits>


QEdge_NS::Edge QEdge_NS::Edge::oNext() const { return d_loop->next(); }
QEdge_NS::Edge QEdge_NS::Edge::oPrev() const { return d_loop->dual().next().dual(); }
QEdge_NS::Edge QEdge_NS::Edge::dNext() const { return d_loop->dual().dual().next().dual().dual(); }
QEdge_NS::Edge QEdge_NS::Edge::dPrev() const { return d_loop->dual().dual().dual().next().dual().dual().dual(); }
QEdge_NS::Edge QEdge_NS::Edge::lNext() const { return d_loop->dual().dual().dual().next().dual(); }
QEdge_NS::Edge QEdge_NS::Edge::lPrev() const { return d_loop->next().dual().dual(); }
QEdge_NS::Edge QEdge_NS::Edge::rNext() const { return d_loop->dual().next().dual().dual().dual(); }
QEdge_NS::Edge QEdge_NS::Edge::rPrev() const { return d_loop->dual().dual().next(); }

QEdge_NS::Edge QEdge_NS::Edge::sym() const { return d_loop->dual().dual(); }

QEdge_NS::Vert& QEdge_NS::Edge::o() { return d_loop->vert(); }
QEdge_NS::Vert& QEdge_NS::Edge::d() { return d_loop->dual().dual().vert(); }
QEdge_NS::Face& QEdge_NS::Edge::l() { return d_loop->dual().dual().dual().vert(); }
QEdge_NS::Face& QEdge_NS::Edge::r() { return d_loop->dual().vert(); }

QEdge_NS::Edge::Prim& QEdge_NS::Edge::n() { return d_loop->edge(); }
QEdge_NS::Edge::Prim& QEdge_NS::Edge::s() { return d_loop->dual().dual().edge(); }
QEdge_NS::Edge::Dual& QEdge_NS::Edge::e() { return d_loop->dual().dual().dual().edge(); }
QEdge_NS::Edge::Dual& QEdge_NS::Edge::w() { return d_loop->dual().edge(); }


void QEdge_NS::Edge::splice0( Edge e ) { d_loop->splice0( *e.d_loop ); }
void QEdge_NS::Edge::splice1( Edge e ) { d_loop->splice1( *e.d_loop ); }