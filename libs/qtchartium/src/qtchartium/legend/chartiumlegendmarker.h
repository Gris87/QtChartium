#pragma once



#include "src/qtchartium/legend/ichartiumlegendmarker.h"



class ChartiumLegendMarker : public IChartiumLegendMarker
{
    Q_OBJECT

public:
    explicit ChartiumLegendMarker(IChartiumLegend* legend, QObject* parent = nullptr);
    ~ChartiumLegendMarker() override;

    ChartiumLegendMarker(const ChartiumLegendMarker& another)            = delete;
    ChartiumLegendMarker& operator=(const ChartiumLegendMarker& another) = delete;

    LegendMarkerType type() override;

    QString label() const override;
    void    setLabel(const QString& label) override;

    QBrush labelBrush() const override;
    void   setLabelBrush(const QBrush& brush) override;

    QFont font() const override;
    void  setFont(const QFont& font) override;

    QPen pen() const override;
    void setPen(const QPen& pen) override;

    QBrush brush() const override;
    void   setBrush(const QBrush& brush) override;

    bool isVisible() const override;
    void setVisible(bool visible) override;

    IChartiumLegend::MarkerShape shape() const override;
    void                         setShape(IChartiumLegend::MarkerShape shape) override;

    IChartiumSeries* series() override;

    IChartiumLegendMarkerItem* item() const override;

    QObject* relatedObject() override;

    void invalidateLegend() override;
    void invalidateAllItems() override;

    IChartiumLegend* legend() const override;

public slots:
    void updated() override;
    void handleShapeChange() override;

protected:
    IChartiumLegendMarkerItem* m_item;
    IChartiumLegend*           m_legend;
    bool                       m_customLabel;
    bool                       m_customBrush;
    bool                       m_customPen;
};
