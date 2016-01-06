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

QEdge_NS::Vert& QEdge_NS::Edge::o() const { return d_loop->core(); }
QEdge_NS::Vert& QEdge_NS::Edge::d() const { return d_loop->dual().dual().core(); }
QEdge_NS::Face& QEdge_NS::Edge::l() const { return d_loop->dual().dual().dual().core(); }
QEdge_NS::Face& QEdge_NS::Edge::r() const { return d_loop->dual().core(); }

size_t QEdge_NS::Edge::id() const { return d_loop->id(); }

void QEdge_NS::Edge::splice0( Edge e ) { d_loop->splice0( *e.d_loop ); }
void QEdge_NS::Edge::splice1( Edge e ) { d_loop->splice1( *e.d_loop ); }