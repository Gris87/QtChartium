#pragma once



#include "src/qtchartium/axis/barcategoryaxis/ichartiumbarcategoryaxis.h"



class ChartiumBarCategoryAxis : public IChartiumBarCategoryAxis
{
    Q_OBJECT

public:
    explicit ChartiumBarCategoryAxis(QObject* parent = nullptr);
    ~ChartiumBarCategoryAxis() override;

    ChartiumBarCategoryAxis(const ChartiumBarCategoryAxis& another)            = delete;
    ChartiumBarCategoryAxis& operator=(const ChartiumBarCategoryAxis& another) = delete;

    AxisType type() const override;

    void        append(const QStringList& categories) override;
    void        append(const QString& category) override;
    void        remove(const QString& category) override;
    void        insert(int index, const QString& category) override;
    void        replace(const QString& oldCategory, const QString& newCategory) override;
    void        clear() override;
    void        setCategories(const QStringList& categories) override;
    QStringList categories() override;
    int         count() const override;
    QString     at(int index) const override;

    void    setMin(const QString& minCategory) override;
    QString min() const override;
    void    setMax(const QString& maxCategory) override;
    QString max() const override;
    void    setRange(const QString& minCategory, const QString& maxCategory) override;

    void updateCategoryDomain() override;

    void initializeGraphics(QGraphicsItem* parent) override;
    void initializeDomain(IChartiumDomain* domain) override;

    void setRange(const QVariant& min, const QVariant& max) override;
    void setMin(const QVariant& min) override;
    void setMax(const QVariant& max) override;

    qreal minReal() override;
    qreal maxReal() override;
    void  setRange(qreal min, qreal max) override;

protected:
    QStringList mCategories;
    QString     mMinCategory;
    QString     mMaxCategory;
    qreal       mMin;
    qreal       mMax;
    int         mCount;
};
