#include <format>
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "ecs_controller.h"

using Json = nlohmann::json;

struct Transform {
    int x;
    int y;
    static constexpr std::string_view scene_name() { return "Transform"; }
    static Transform from_json(const Json& j) {
        return Transform{.x = j["x"].get<int>(), .y = j["y"].get<int>()};
    }
};

class SceneComponentTest : public ::testing::Test {
   protected:
    void SetUp() override {
        ecs.register_component<Transform>();
    }

    garnish::ECSController ecs;
};

TEST_F(SceneComponentTest, EntitiesDoNotHaveComponentsBeforeLoading) {
    auto ent1 = ecs.create_entity();
    auto ent2 = ecs.create_entity();

    EXPECT_FALSE(ecs.has_component<Transform>(ent1));
    EXPECT_FALSE(ecs.has_component<Transform>(ent2));
}

TEST_F(SceneComponentTest, LoadComponentsFromJson) {
    auto ent1 = ecs.create_entity();
    auto ent2 = ecs.create_entity();

    ecs.load_entity(ent1, Json{{"Transform", {{"x", 10}, {"y", 20}}}});
    ecs.load_entity(ent2, Json{{"Transform", {{"x", 30}, {"y", 40}}}});

    EXPECT_TRUE(ecs.has_component<Transform>(ent1));
    EXPECT_TRUE(ecs.has_component<Transform>(ent2));

    auto& transform1 = ecs.get_component<Transform>(ent1);
    EXPECT_EQ(transform1.x, 10);
    EXPECT_EQ(transform1.y, 20);

    auto& transform2 = ecs.get_component<Transform>(ent2);
    EXPECT_EQ(transform2.x, 30);
    EXPECT_EQ(transform2.y, 40);
}

TEST_F(SceneComponentTest, ComponentsCanBeModified) {
    auto ent1 = ecs.create_entity();
    ecs.load_entity(ent1, Json{{"Transform", {{"x", 10}, {"y", 20}}}});

    auto& transform1 = ecs.get_component<Transform>(ent1);
    transform1.x = 100;
    transform1.y = 200;

    auto& transform1_modified = ecs.get_component<Transform>(ent1);
    EXPECT_EQ(transform1_modified.x, 100);
    EXPECT_EQ(transform1_modified.y, 200);
}

TEST_F(SceneComponentTest, MultipleEntitiesWithDifferentValues) {
    auto ent1 = ecs.create_entity();
    auto ent2 = ecs.create_entity();
    auto ent3 = ecs.create_entity();

    ecs.load_entity(ent1, Json{{"Transform", {{"x", 10}, {"y", 20}}}});
    ecs.load_entity(ent2, Json{{"Transform", {{"x", 30}, {"y", 40}}}});
    ecs.load_entity(ent3, Json{{"Transform", {{"x", 50}, {"y", 60}}}});

    EXPECT_TRUE(ecs.has_component<Transform>(ent1));
    EXPECT_TRUE(ecs.has_component<Transform>(ent2));
    EXPECT_TRUE(ecs.has_component<Transform>(ent3));

    EXPECT_EQ(ecs.get_component<Transform>(ent1).x, 10);
    EXPECT_EQ(ecs.get_component<Transform>(ent1).y, 20);
    EXPECT_EQ(ecs.get_component<Transform>(ent2).x, 30);
    EXPECT_EQ(ecs.get_component<Transform>(ent2).y, 40);
    EXPECT_EQ(ecs.get_component<Transform>(ent3).x, 50);
    EXPECT_EQ(ecs.get_component<Transform>(ent3).y, 60);
}

TEST_F(SceneComponentTest, EntityDestruction) {
    auto ent1 = ecs.create_entity();
    auto ent2 = ecs.create_entity();
    auto ent3 = ecs.create_entity();

    ecs.load_entity(ent1, Json{{"Transform", {{"x", 10}, {"y", 20}}}});
    ecs.load_entity(ent2, Json{{"Transform", {{"x", 30}, {"y", 40}}}});
    ecs.load_entity(ent3, Json{{"Transform", {{"x", 50}, {"y", 60}}}});

    ecs.destroy_entity(ent1);
    EXPECT_EQ(ent1, garnish::DEAD_ENTITY);

    EXPECT_TRUE(ecs.has_component<Transform>(ent2));
    EXPECT_TRUE(ecs.has_component<Transform>(ent3));

    ecs.destroy_entity(ent2);
    EXPECT_EQ(ent2, garnish::DEAD_ENTITY);

    EXPECT_TRUE(ecs.has_component<Transform>(ent3));
}

TEST_F(SceneComponentTest, EntityReuseAfterDestruction) {
    auto ent1 = ecs.create_entity();
    ecs.load_entity(ent1, Json{{"Transform", {{"x", 10}, {"y", 20}}}});

    ecs.destroy_entity(ent1);
    EXPECT_EQ(ent1, garnish::DEAD_ENTITY);

    auto ent4 = ecs.create_entity();
    EXPECT_NE(ent4, garnish::DEAD_ENTITY);
    EXPECT_FALSE(ecs.has_component<Transform>(ent4));

    ecs.load_entity(ent4, Json{{"Transform", {{"x", 70}, {"y", 80}}}});
    EXPECT_TRUE(ecs.has_component<Transform>(ent4));
    EXPECT_EQ(ecs.get_component<Transform>(ent4).x, 70);
    EXPECT_EQ(ecs.get_component<Transform>(ent4).y, 80);
}
