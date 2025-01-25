// Animasi bahan mengecil sebelum menghilang
for (auto& ingredient : ingredients) {
    if (ingredient.chopped && ingredient.shape.getSize().x > 0) {
        sf::Vector2f size = ingredient.shape.getSize();
        ingredient.shape.setSize(sf::Vector2f(size.x - 1, size.y - 0.5)); // Mengecil perlahan
        ingredient.shape.setOrigin(size.x / 2, size.y / 2);
        ingredient.shape.setPosition(ingredient.shape.getPosition().x + 0.5f, ingredient.shape.getPosition().y + 0.25f);
    }
}
