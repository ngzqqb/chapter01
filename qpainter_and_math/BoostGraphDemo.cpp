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

            /*更新广度值*/
            const auto varRow = g[v0].breadth + 1;
            const_cast<G &>(g)[v1].breadth = varRow;

            /*计算可见对象位置*/
            if (varRow != thisCurrentRow) {
                thisColumnPos = 0;
                thisRowPos += 36;
                thisCurrentRow = varRow;
            } else {
                thisColumnPos += 40;
            }
            g[v1].item->setPos(thisColumnPos, thisRowPos);

            /*绘制连接线*/
            auto varLine = sstd_new<ConnectVisibleNodeLine>(
                g[v0].item, g[v1].item);
            thisScene->addItem(varLine);

        }

        inline BFSVisiter(QGraphicsScene * arg) :thisScene(arg) {
        }

    private:
        mutable std::size_t thisCurrentRow{ 0 };
        mutable qreal thisColumnPos{ -40 };
        mutable qreal thisRowPos{ 0 };
        QGraphicsScene * thisScene{ nullptr };
    };

    BoostGraphDemo::BoostGraphDemo() :
        SubWindowBasic(QStringLiteral("BoostGraphDemo")) {

        auto varScene = this->scene();

        using Graph = boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, NodeData>;

        Graph varGraph;

        /*构造图*/
        boost::add_edge(0, 1, varGraph);
        boost::add_edge(5, 7, varGraph);
        boost::add_edge(0, 2, varGraph);
        boost::add_edge(2, 4, varGraph);
        boost::add_edge(0, 3, varGraph);
        boost::add_edge(2, 5, varGraph);
        boost::add_edge(2, 6, varGraph);

        /*进行拓扑排序*/
        boost::depth_first_search(varGraph, boost::visitor(DFSVisiter{ varGraph }));

        {/*初始化可见元素*/
            auto[varPos, varEnd] = boost::vertices(varGraph);
            for (; varPos != varEnd; ++varPos) {
                auto varItem = sstd_new<VisibleNodeItem>(
                    QString::number(varGraph[*varPos].depth), 0, 0);
                varGraph[*varPos].item = varItem;
                varScene->addItem(varItem);
            }
        }

        /*绘制可见元素*/
        boost::breadth_first_search(varGraph, 0, boost::visitor(BFSVisiter{ varScene }));

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

        varDx *= varOffset.x();
        varDy *= varOffset.x();

        this->setLine(var0.x() - varDx, var0.y() - varDy,
            var1.x() + varDx, var1.y() + varDy);

    }

}/*namespace sstd*/

/*endl_input_of_latex_for_clanguage_lick*/
// https://www.boost.org/doc/libs/1_57_0/libs/graph/doc/graph_concepts.html





















