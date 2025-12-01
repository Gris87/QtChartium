#include "src/qtchartium/axis/barcategoryaxis/chartiumbarcategoryaxis.h"

#include "src/qtchartium/ichartiumchart.h"



ChartiumBarCategoryAxis::ChartiumBarCategoryAxis(QObject* parent) :
    IChartiumBarCategoryAxis(parent),
    mCategories(),
    mMinCategory(),
    mMaxCategory(),
    mMin(),
    mMax(),
    mCount()
{
}

ChartiumBarCategoryAxis::~ChartiumBarCategoryAxis()
{
    if (mChart != nullptr)
    {
        mChart->removeAxis(this);
    }
}

IChartiumAxis::AxisType ChartiumBarCategoryAxis::type() const
{
    return IChartiumAxis::AxisTypeBarCategory;
}

void ChartiumBarCategoryAxis::append(const QStringList& categories)
{
    if (categories.isEmpty())
    {
        return;
    }

    int count = mCategories.size();

    foreach(QString category, categories)
    {
        if (!mCategories.contains(category) && !category.isNull())
        {
            mCategories.append(category);
        }
    }

    if (mCategories.size() == count)
    {
        return;
    }

    if (count == 0)
    {
        setRange(mCategories.first(), mCategories.last());
    }
    else
    {
        setRange(mMinCategory, mCategories.last());
    }

    emit categoriesChanged();
    emit countChanged();
}

void ChartiumBarCategoryAxis::append(const QString& category)
{
    int count = mCategories.size();

    if (!mCategories.contains(category) && !category.isNull())
    {
        mCategories.append(category);
    }

    if (mCategories.size() == count)
    {
        return;
    }

    if (count == 0)
    {
        setRange(mCategories.last(), mCategories.last());
    }
    else
    {
        setRange(mMinCategory, mCategories.last());
    }

    emit categoriesChanged();
    emit countChanged();
}

void ChartiumBarCategoryAxis::remove(const QString& category)
{
    if (mCategories.contains(category))
    {
        mCategories.removeAt(mCategories.indexOf(category));

        if (!mCategories.isEmpty())
        {
            if (mMinCategory == category)
            {
                setRange(mCategories.first(), mMaxCategory);
            }
            else if (mMaxCategory == category)
            {
                setRange(mMinCategory, mCategories.last());
            }
            else
            {
                updateCategoryDomain();
            }
        }
        else
        {
            setRange(QString(), QString());
        }

        emit categoriesChanged();
        emit countChanged();
    }
}

void ChartiumBarCategoryAxis::insert(int index, const QString& category)
{
    int count = mCategories.size();

    if (!mCategories.contains(category) && !category.isNull())
    {
        mCategories.insert(index, category);
    }

    if (mCategories.size() == count)
    {
        return;
    }

    if (count == 0)
    {
        setRange(mCategories.first(), mCategories.first());
    }
    else if (index == 0)
    {
        setRange(mCategories.first(), mMaxCategory);
    }
    else if (index == count)
    {
        setRange(mMinCategory, mCategories.last());
    }
    else
    {
        updateCategoryDomain();
    }

    emit categoriesChanged();
    emit countChanged();
}

void ChartiumBarCategoryAxis::replace(const QString& oldCategory, const QString& newCategory)
{
    int pos = mCategories.indexOf(oldCategory);

    if (pos != -1 && !mCategories.contains(newCategory) && !newCategory.isNull())
    {
        mCategories.replace(pos, newCategory);

        if (mMinCategory == oldCategory)
        {
            setRange(newCategory, mMaxCategory);
        }
        else if (mMaxCategory == oldCategory)
        {
            setRange(mMinCategory, newCategory);
        }

        emit categoriesChanged();
        emit countChanged();
    }
}

void ChartiumBarCategoryAxis::clear()
{
    mCategories.clear();

    setRange(QString(), QString());

    emit categoriesChanged();
    emit countChanged();
}

void ChartiumBarCategoryAxis::setCategories(const QStringList& categories)
{
    mCategories.clear();
    mMinCategory = QString();
    mMaxCategory = QString();
    mMin         = 0;
    mMax         = 0;
    mCount       = 0;

    append(categories);
}

QStringList ChartiumBarCategoryAxis::categories()
{
    return mCategories;
}

int ChartiumBarCategoryAxis::count() const
{
    return mCategories.size();
}

QString ChartiumBarCategoryAxis::at(int index) const
{
    return mCategories.at(index);
}

void ChartiumBarCategoryAxis::setMin(const QString& minCategory)
{
    setRange(minCategory, mMaxCategory);
}

QString ChartiumBarCategoryAxis::min() const
{
    return mMinCategory;
}

void ChartiumBarCategoryAxis::setMax(const QString& maxCategory)
{
    setRange(mMinCategory, maxCategory);
}

QString ChartiumBarCategoryAxis::max() const
{
    return mMaxCategory;
}

void ChartiumBarCategoryAxis::setRange(const QString& minCategory, const QString& maxCategory)
{
    bool changed = false;

    //special case in case or clearing all categories
    if (minCategory.isNull() && maxCategory.isNull())
    {
        mMinCategory = minCategory;
        mMaxCategory = maxCategory;
        mMin         = 0;
        mMax         = 0;
        mCount       = 0;

        emit minChanged(minCategory);
        emit maxChanged(maxCategory);
        emit rangeChanged(mMinCategory, mMaxCategory);
        emit rangeRealChanged(mMin, mMax);

        return;
    }

    if (mCategories.indexOf(maxCategory) < mCategories.indexOf(minCategory))
    {
        return;
    }

    if (!minCategory.isNull() && (mMinCategory != minCategory || mMinCategory.isNull()) && mCategories.contains(minCategory))
    {
        mMinCategory = minCategory;
        mMin         = mCategories.indexOf(mMinCategory) - 0.5;
        changed      = true;

        emit minChanged(minCategory);
    }

    if (!maxCategory.isNull() && (mMaxCategory != maxCategory || mMaxCategory.isNull()) && mCategories.contains(maxCategory))
    {
        mMaxCategory = maxCategory;
        mMax         = mCategories.indexOf(mMaxCategory) + 0.5;
        changed      = true;

        emit maxChanged(maxCategory);
    }

    if (changed)
    {
        mCount = mMax - mMin;

        emit rangeChanged(mMinCategory, mMaxCategory);
        emit rangeRealChanged(mMin, mMax);
    }
}

void ChartiumBarCategoryAxis::updateCategoryDomain()
{
    bool changed = false;

    qreal tmpMin = mCategories.indexOf(mMinCategory) - 0.5;

    if (!qFuzzyIsNull(mMin - tmpMin))
    {
        mMin    = tmpMin;
        changed = true;
    }

    qreal tmpMax = mCategories.indexOf(mMaxCategory) + 0.5;

    if (!qFuzzyIsNull(mMax - tmpMax))
    {
        mMax    = tmpMax;
        changed = true;
    }

    mCount = mMax - mMin;

    if (changed)
    {
        emit rangeRealChanged(mMin, mMax);
    }
}

void ChartiumBarCategoryAxis::initializeGraphics(QGraphicsItem* parent)
{
    IChartiumAxisElement* axis = nullptr;

    // TODO: Uncomment
    /*
    if (orientation() == Qt::Vertical)
    {
        axis = new ChartBarCategoryAxisY(q, parent);
    }
    if (orientation() == Qt::Horizontal)
    {
        axis = new ChartBarCategoryAxisX(q, parent);
    }
    */

    mItem = axis;
    IChartiumBarCategoryAxis::initializeGraphics(parent);
}

void ChartiumBarCategoryAxis::initializeDomain(IChartiumDomain* domain)
{
    if (mMax == mMin)
    {
        int min;
        int max;

        if (orientation() == Qt::Vertical)
        {
            min = domain->minY() + 0.5;
            max = domain->maxY() - 0.5;
        }
        else
        {
            min = domain->minX() + 0.5;
            max = domain->maxX() - 0.5;
        }

        if (min > 0 && min < mCategories.size() && max > 0 && max < mCategories.size())
        {
            setRange(mCategories.at(min), mCategories.at(max));
        }
    }
    else
    {
        if (orientation() == Qt::Vertical)
        {
            domain->setRangeY(mMin, mMax);
        }
        else
        {
            domain->setRangeX(mMin, mMax);
        }
    }
}

void ChartiumBarCategoryAxis::setRange(const QVariant& min, const QVariant& max)
{
    QString value1 = min.toString();
    QString value2 = max.toString();

    setRange(value1, value2);
}

void ChartiumBarCategoryAxis::setMin(const QVariant& min)
{
    setRange(min, mMaxCategory);
}

void ChartiumBarCategoryAxis::setMax(const QVariant& max)
{
    setRange(mMinCategory, max);
}

qreal ChartiumBarCategoryAxis::minReal()
{
    return mMin;
}

qreal ChartiumBarCategoryAxis::maxReal()
{
    return mMax;
}

void ChartiumBarCategoryAxis::setRange(qreal min, qreal max)
{
    bool categoryChanged = false;
    bool changed         = false;

    if (min > max)
    {
        return;
    }

    if (!qFuzzyIsNull(mMin - min))
    {
        mMin    = min;
        changed = true;

        int imin = mMin + 0.5;

        if (imin >= 0 && imin < mCategories.size())
        {
            QString minCategory = mCategories.at(imin);

            if (mMinCategory != minCategory && !minCategory.isEmpty())
            {
                mMinCategory    = minCategory;
                categoryChanged = true;
                emit minChanged(minCategory);
            }
        }
    }

    if (!qFuzzyIsNull(mMax - max))
    {
        mMax    = max;
        changed = true;

        int imax = mMax - 0.5;

        if (imax >= 0 && imax < mCategories.size())
        {
            QString maxCategory = mCategories.at(imax);

            if (mMaxCategory != maxCategory && !maxCategory.isEmpty())
            {
                mMaxCategory    = maxCategory;
                categoryChanged = true;
                emit maxChanged(maxCategory);
            }
        }
    }

    if (categoryChanged)
    {
        emit rangeChanged(mMinCategory, mMaxCategory);
    }

    if (changed)
    {
        emit rangeRealChanged(mMin, mMax);
    }
}
