#include "BoostGraphDemo.hpp"

#include <sstd/boost/graph/adjacency_list.hpp>
#include <sstd/boost/graph/depth_first_search.hpp>
#include <sstd/boost/graph/breadth_first_search.hpp>

namespace sstd {

    class NodeData {
    public:
        std::size_t depth{ 0 };
        std::size_t breadth{ 0 };
        VisibleNodeItem * item{ nullptr };
    private:
        sstd_class(NodeData);
    };

    class DFSVisiter : public boost::default_dfs_visitor {
    public:
        template<typename V, typename G>
        inline void finish_vertex(const V & v, const G & g) const {
            const_cast<G &>(g)[v].depth = --thisIndex;
        }
        template<typename G>
        inline DFSVisiter(const G & g) {
            thisIndex = boost::num_vertices(g);
        }
        mutable std::size_t thisIndex{ 0 };
    };

    class BFSVisiter : public boost::default_bfs_visitor {
    public:
        template<typename E, typename G>
        inline void tree_edge(const E & e, const G & g) const {
            const auto & v0 = boost::source(e, g);
            const auto & v1 = boost::target(e, g);
            const_cast<G &>(g)[v1].breadth = g[v0].breadth + 1;
        }
    };

    class DrawVisiter : public boost::default_bfs_visitor {
    public:
        template<typename V, typename G>
        inline void discover_vertex(const V & v, const G & g) const {
            auto varRow = g[v].breadth;
            if (varRow != thisCurrentRow) {
                thisColumnPos = 0;
                thisRowPos += 36;
                thisCurrentRow = varRow;
            } else {
                thisColumnPos += 40;
            }
            g[v].item->setPos(thisColumnPos, thisRowPos);
        }
        template<typename E, typename G>
        inline void tree_edge(const E & e, const G & g) const {
            const auto & v0 = boost::source(e, g);
            const auto & v1 = boost::target(e, g);
            auto varLine = sstd_new<ConnectVisibleNodeLine>(
                g[v0].item, g[v1].item);
            thisLines.push_back(varLine);
            thisScene->addItem(varLine);
        }
        inline DrawVisiter(QGraphicsScene * arg) : thisScene{ arg } {
        }
        inline ~DrawVisiter() {
            for (auto & varI : thisLines) {
                varI->visibleItemChanged();
            }
        }
        mutable std::size_t thisCurrentRow{ 0 };
        mutable qreal thisColumnPos{ -40 };
        mutable qreal thisRowPos{ 0 };
        QGraphicsScene * thisScene{ nullptr };
        mutable std::vector< ConnectVisibleNodeLine * > thisLines;
    };

    BoostGraphDemo::BoostGraphDemo() :
        SubWindowBasic(QStringLiteral("BoostGraphDemo")) {

        auto varScene = this->scene();

        using Graph = boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, NodeData>;

        Graph varGraph;

        boost::add_edge(0, 1, varGraph);
        boost::add_edge(0, 2, varGraph);
        boost::add_edge(0, 3, varGraph);
        boost::add_edge(2, 4, varGraph);
        boost::add_edge(2, 5, varGraph);
        boost::add_edge(2, 6, varGraph);
        boost::add_edge(5, 7, varGraph);

        boost::depth_first_search(varGraph, boost::visitor(DFSVisiter{ varGraph }));
        boost::breadth_first_search(varGraph, 0, boost::visitor(BFSVisiter{}));

        {
            auto[varPos, varEnd] = boost::vertices(varGraph);
            for (; varPos != varEnd; ++varPos) {
                auto varItem = sstd_new<VisibleNodeItem>(
                    QString::number(varGraph[*varPos].depth), 0, 0);
                varGraph[*varPos].item = varItem;
                varScene->addItem(varItem);
            }
        }

        boost::breadth_first_search(varGraph, 0, boost::visitor(DrawVisiter{ varScene }));

    }

    constexpr qreal globalVisibleNodeItemSize = 28;

    VisibleNodeItem::VisibleNodeItem(const QString & argText,
        const qreal & argX,
        const qreal & argY) :
        QGraphicsEllipseItem(-0.5*globalVisibleNodeItemSize,
            -0.5*globalVisibleNodeItemSize,
            globalVisibleNodeItemSize,
            globalVisibleNodeItemSize) {
        this->setPos(argX, argY);
        auto varText = sstd_virtual_new<QGraphicsTextItem>(argText);
        varText->setParentItem(this);
        varText->setPos(-varText->boundingRect().center());
        this->setFlag(ItemIsMovable);
        this->setFlag(ItemSendsGeometryChanges);
    }

    void VisibleNodeItem::updatePos(ConnectVisibleNodeLine * arg) {
        arg->visibleItemChanged();
    }

    void VisibleNodeItem::attacheLine(ConnectVisibleNodeLine * arg) {
        if (arg&&thisLines.insert(arg).second) {
            updatePos(arg);
        }
    }

    QVariant VisibleNodeItem::itemChange(
        QGraphicsItem::GraphicsItemChange change,
        const QVariant &value) {
        if ((ItemPositionChange == change) && scene()) {
            for (const auto & varI : thisLines) {
                updatePos(varI);
            }
        }
        return QGraphicsEllipseItem::itemChange(change, value);
    }

    ConnectVisibleNodeLine::ConnectVisibleNodeLine(VisibleNodeItem* argA,
        VisibleNodeItem* argB) {
        thisLine0 = argA;
        thisLine1 = argB;
        argA->attacheLine(this);
        argB->attacheLine(this);
    }

    void ConnectVisibleNodeLine::visibleItemChanged() {

        const constexpr QPointF varOffset{
            globalVisibleNodeItemSize*0.5,
            globalVisibleNodeItemSize*0.5
        };

        const auto var0 = thisLine0->pos();
        const auto var1 = thisLine1->pos();

        auto varDx = var0.x() - var1.x();
        auto varDy = var0.y() - var1.y();
        auto varLineLength = std::hypot(varDx, varDy);

        if (varLineLength <= std::numeric_limits<float>::epsilon()) {
            varDx = 1;
            varDy = 0;
        } else {
            varDx /= varLineLength;
            varDy /= varLineLength;
        }

        varDx *= globalVisibleNodeItemSize * 0.5;
        varDy *= globalVisibleNodeItemSize * 0.5;

        this->setLine(var0.x() - varDx, var0.y() - varDy,
            var1.x() + varDx, var1.y() + varDy);

    }

}/*namespace sstd*/

// https://www.boost.org/doc/libs/1_57_0/libs/graph/doc/graph_concepts.html





















