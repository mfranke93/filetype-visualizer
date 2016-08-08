#include "../third_party/catch/catch.hpp"
#include "../vis/image.hpp"
#include "../vis/image_builder.hpp"
#include "../vis/standard_colormap.hpp"
#include "../except/illegal_size_exception.hpp"

SCENARIO ("Building an Image from data")
{
    GIVEN ("A vector of normalized values and a colormap")
    {
        std::shared_ptr<std::vector<double>> values = std::make_shared<std::vector<double>>();
        values->push_back(0.0);
        values->push_back(0.5);
        values->push_back(0.5);
        values->push_back(1.0);
        std::shared_ptr<vis::Colormap const> colormap = vis::StandardColormap::getPredefinedColormap(vis::PredefinedColormaps::RED_BLUE);

        WHEN ("Building an image from this")
        {
            std::shared_ptr<vis::Image> img = vis::ImageBuilder::buildImageFromData(2, 2, values, colormap);

            THEN ("The upper left pixel is red")
            {
                vis::color const reference (255, 0, 0);
                vis::color const compare = img->operator()(0,0);

                REQUIRE(reference.R == compare.R);
                REQUIRE(reference.G == compare.G);
                REQUIRE(reference.B == compare.B);
            }
            THEN ("The upper right pixel is white")
            {
                vis::color const reference (255, 255, 255);
                vis::color const compare = img->operator()(1,0);

                REQUIRE(reference.R == compare.R);
                REQUIRE(reference.G == compare.G);
                REQUIRE(reference.B == compare.B);
            }
            THEN ("The lower left pixel is white")
            {
                vis::color const reference (255, 255, 255);
                vis::color const compare = img->operator()(0,1);

                REQUIRE(reference.R == compare.R);
                REQUIRE(reference.G == compare.G);
                REQUIRE(reference.B == compare.B);
            }
            THEN ("The lower right pixel is blue")
            {
                vis::color const reference (0, 0, 255);
                vis::color const compare = img->operator()(1,1);

                REQUIRE(reference.R == compare.R);
                REQUIRE(reference.G == compare.G);
                REQUIRE(reference.B == compare.B);
            }
        }
    }
}

SCENARIO ("Building an Image from data, illegal width or height")
{
    GIVEN ("A vector of normalized values and a colormap")
    {
        std::shared_ptr<std::vector<double>> values = std::make_shared<std::vector<double>>();
        values->push_back(0.0);
        values->push_back(0.5);
        values->push_back(0.5);
        values->push_back(1.0);
        std::shared_ptr<vis::Colormap const> colormap = vis::StandardColormap::getPredefinedColormap(vis::PredefinedColormaps::RED_BLUE);

        WHEN ("Building an image from this with width 0")
        {
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(vis::ImageBuilder::buildImageFromData(0, 4, values, colormap), except::illegal_size);
            }
        }

        WHEN ("Building an image from this with height 0")
        {
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(vis::ImageBuilder::buildImageFromData(4, 0, values, colormap), except::illegal_size);
            }
        }

        WHEN ("Building an image from this with width and height such that too few values are given")
        {
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(vis::ImageBuilder::buildImageFromData(4, 4, values, colormap), except::illegal_size);
            }
        }

        WHEN ("Building an image from this with width and height such that too many values are given")
        {
            THEN ("an exception should be thrown")
            {
                REQUIRE_THROWS_AS(vis::ImageBuilder::buildImageFromData(2, 1, values, colormap), except::illegal_size);
            }
        }
    }
}

SCENARIO ("Unnormalized data passed to ImageBuilder")
{
    GIVEN ("A vector of normalized values with one value larger 1.0 and a colormap")
    {
        std::shared_ptr<std::vector<double>> values = std::make_shared<std::vector<double>>();
        values->push_back(0.0);
        values->push_back(0.5);
        values->push_back(0.5);
        values->push_back(1.0000001);
        std::shared_ptr<vis::Colormap const> colormap = vis::StandardColormap::getPredefinedColormap(vis::PredefinedColormaps::RED_BLUE);

        WHEN ("trying to get an image from this")
        {
            THEN ("a normalizer error should occur")
            {
                REQUIRE_THROWS_AS(vis::ImageBuilder::buildImageFromData(2, 2, values, colormap), except::normalizer_exception);
            }
        }
    }

    GIVEN ("A vector of normalized values with one value smaller than 0.0 and a colormap")
    {
        std::shared_ptr<std::vector<double>> values = std::make_shared<std::vector<double>>();
        values->push_back(-0.00001);
        values->push_back(0.5);
        values->push_back(0.5);
        values->push_back(1.0);
        std::shared_ptr<vis::Colormap const> colormap = vis::StandardColormap::getPredefinedColormap(vis::PredefinedColormaps::RED_BLUE);

        WHEN ("trying to get an image from this")
        {
            THEN ("a normalizer error should occur")
            {
                REQUIRE_THROWS_AS(vis::ImageBuilder::buildImageFromData(2, 2, values, colormap), except::normalizer_exception);
            }
        }
    }
}
