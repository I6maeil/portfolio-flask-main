C:\Users\benis\OneDrive\Desktop\Portfeuille
│
├── app.py
├── templates/
│     └── index.html     <!DOCTYPE html>
<html lang="fr">    
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Portfolio Professionnel | Développeur Web</title>
    <script src="https://cdn.tailwindcss.com"></script>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css">
    <style>
        .hero-gradient {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
        }
        .section-divider {
            height: 100px;
            background: linear-gradient(to bottom right, transparent 49%, #f8fafc 50%), 
                        linear-gradient(to bottom left, transparent 49%, #f8fafc 50%);
        }
        .skill-bar {
            transition: width 1.5s ease-in-out;
        }
        .project-card {
            transition: transform 0.3s ease, box-shadow 0.3s ease;
        }
        .project-card:hover {
            transform: translateY(-5px);
            box-shadow: 0 20px 25px -5px rgba(0, 0, 0, 0.1), 0 10px 10px -5px rgba(0, 0, 0, 0.04);
        }
        .menu-open {
            transform: translateX(0);
        }
    </style>
</head>
<body class="bg-gray-50 text-gray-800 font-sans">
    <!-- Navigation -->
    <nav class="fixed w-full bg-white shadow-md z-50">
        <div class="container mx-auto px-6 py-4 flex justify-between items-center">
            <a href="#" class="text-2xl font-bold text-indigo-600">#<span class="text-purple-600"></span></a>
            
            <div class="hidden md:flex space-x-8">
                <a href="#accueil" class="hover:text-indigo-600 transition-colors">Accueil</a>
                <a href="#competences" class="hover:text-indigo-600 transition-colors">Compétences</a>
                <a href="#portfolio" class="hover:text-indigo-600 transition-colors">Portfolio</a>
                <a href="#experience" class="hover:text-indigo-600 transition-colors">Expérience</a>
                <a href="#contact" class="hover:text-indigo-600 transition-colors">Contact</a>
            </div>
            
            <button id="menu-toggle" class="md:hidden text-gray-600">
                <i class="fas fa-bars text-2xl"></i>
            </button>
        </div>
        
        <!-- Mobile Menu -->
        <div id="mobile-menu" class="fixed inset-0 bg-white z-40 transform -translate-x-full transition-transform md:hidden">
            <div class="flex justify-end p-6">
                <button id="menu-close" class="text-2xl text-gray-600">
                    <i class="fas fa-times"></i>
                </button>
            </div>
            <div class="flex flex-col items-center justify-center space-y-8 h-full">
                <a href="#accueil" class="text-xl hover:text-indigo-600 transition-colors">Accueil</a>
                <a href="#competences" class="text-xl hover:text-indigo-600 transition-colors">Compétences</a>
                <a href="#portfolio" class="text-xl hover:text-indigo-600 transition-colors">Portfolio</a>
                <a href="#experience" class="text-xl hover:text-indigo-600 transition-colors">Expérience</a>
                <a href="#contact" class="text-xl hover:text-indigo-600 transition-colors">Contact</a>
            </div>
        </div>
    </nav>

    <!-- Hero Section -->
    <section id="accueil" class="hero-gradient text-white pt-24 pb-20 md:pt-32 md:pb-28">
        <div class="container mx-auto px-6 flex flex-col md:flex-row items-center">
            <div class="md:w-1/2 mb-10 md:mb-0">
                <h1 class="text-4xl md:text-5xl font-bold mb-4"> WebDéveloppeur  </h1>
                <p class="text-xl mb-8 opacity-90">Je transforme vos idées en solutions digitales innovantes et performantes</p>
                <div class="flex space-x-4">
                    <a href="#portfolio" class="bg-white text-indigo-600 font-semibold py-3 px-6 rounded-lg shadow-lg hover:bg-gray-100 transition-colors">Voir mon travail</a>
                    <a href="#contact" class="border-2 border-white text-white font-semibold py-3 px-6 rounded-lg hover:bg-white hover:text-indigo-600 transition-colors">Me contacter</a>
                </div>
            </div>
            <div class="md:w-1/2 flex justify-center">
                <div class="relative">
                    <div class="w-64 h-64 md:w-80 md:h-80 bg-white bg-opacity-10 rounded-full flex items-center justify-center">
                        <img src="WhatsApp Image 2025-04-29 à 18.12.02_911b5cbb.jpg" 
                             alt="Portrait professionnel d'un développeur web souriant en tenue professionnelle moderne" 
                             class="w-56 h-56 md:w-72 md:h-72 rounded-full object-cover border-4 border-white border-opacity-20">
                    </div>
                    <div class="absolute -bottom-2 -right-2 bg-indigo-500 rounded-full w-16 h-16 flex items-center justify-center">
                        <span class="text-xs font-bold"></span>
                    </div>
                </div>
            </div>
        </div>
    </section>

    <div class="section-divider"></div>

    <!-- Skills Section -->
    <section id="competences" class="py-20 bg-white">
        <div class="container mx-auto px-6">
            <h2 class="text-3xl font-bold text-center mb-4">Mes Compétences</h2>
            <p class="text-gray-600 text-center max-w-2xl mx-auto mb-12">Je maîtrise les technologies modernes pour créer des applications web performantes et évolutives.</p>
            
            <div class="grid grid-cols-1 md:grid-cols-2 gap-8">
                <!-- Frontend Skills -->
                <div class="bg-gray-50 p-6 rounded-xl shadow-sm">
                    <h3 class="text-xl font-semibold mb-4 text-indigo-600">Développement Frontend</h3>
                    <div class="space-y-4">
                        <div>
                            <div class="flex justify-between mb-1">
                                <span>HTML/CSS</span>
                                <span>95%</span>
                            </div>
                            <div class="h-2 bg-gray-200 rounded-full">
                                <div class="h-2 bg-indigo-600 rounded-full skill-bar" style="width: 95%"></div>
                            </div>
                        </div>
                        <div>
                            <div class="flex justify-between mb-1">
                                <span>JavaScript</span>
                                <span>90%</span>
                            </div>
                            <div class="h-2 bg-gray-200 rounded-full">
                                <div class="h-2 bg-indigo-600 rounded-full skill-bar" style="width: 90%"></div>
                            </div>
                        </div>
                        <div>
                            <div class="flex justify-between mb-1">
                                <span>React.js</span>
                                <span>88%</span>
                            </div>
                            <div class="h-2 bg-gray-200 rounded-full">
                                <div class="h-2 bg-indigo-600 rounded-full skill-bar" style="width: 88%"></div>
                            </div>
                        </div>
                        <div>
                            <div class="flex justify-between mb-1">
                                <span>Vue.js</span>
                                <span>85%</span>
                            </div>
                            <div class="h-2 bg-gray-200 rounded-full">
                                <div class="h-2 bg-indigo-600 rounded-full skill-bar" style="width: 85%"></div>
                            </div>
                        </div>
                    </div>
                </div>
                
                <!-- Backend Skills -->
                <div class="bg-gray-50 p-6 rounded-xl shadow-sm">
                    <h3 class="text-xl font-semibold mb-4 text-purple-600">Développement Backend</h3>
                    <div class="space-y-4">
                        <div>
                            <div class="flex justify-between mb-1">
                                <span>Node.js</span>
                                <span>87%</span>
                            </div>
                            <div class="h-2 bg-gray-200 rounded-full">
                                <div class="h-2 bg-purple-600 rounded-full skill-bar" style="width: 87%"></div>
                            </div>
                        </div>
                        <div>
                            <div class="flex justify-between mb-1">
                                <span>Python/Django</span>
                                <span>82%</span>
                            </div>
                            <div class="h-2 bg-gray-200 rounded-full">
                                <div class="h-2 bg-purple-600 rounded-full skill-bar" style="width: 82%"></div>
                            </div>
                        </div>
                        <div>
                            <div class="flex justify-between mb-1">
                                <span>PHP/Laravel</span>
                                <span>80%</span>
                            </div>
                            <div class="h-2 bg-gray-200 rounded-full">
                                <div class="h-2 bg-purple-600 rounded-full skill-bar" style="width: 80%"></div>
                            </div>
                        </div>
                        <div>
                            <div class="flex justify-between mb-1">
                                <span>Bases de données</span>
                                <span>90%</span>
                            </div>
                            <div class="h-2 bg-gray-200 rounded-full">
                                <div class="h-2 bg-purple-600 rounded-full skill-bar" style="width: 90%"></div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            
            <!-- Tools & Technologies -->
            <div class="mt-12">
                <h3 class="text-xl font-semibold text-center mb-8">Outils & Technologies</h3>
                <div class="flex flex-wrap justify-center gap-6">
                    <div class="bg-white p-4 rounded-lg shadow-sm flex items-center">
                        <i class="fab fa-git-alt text-3xl text-orange-600 mr-3"></i>
                        <span>Git</span>
                    </div>
                    <div class="bg-white p-4 rounded-lg shadow-sm flex items-center">
                        <i class="fab fa-docker text-3xl text-blue-600 mr-3"></i>
                        <span>Docker</span>
                    </div>
                    <div class="bg-white p-4 rounded-lg shadow-sm flex items-center">
                        <i class="fab fa-figma text-3xl text-purple-600 mr-3"></i>
                        <span>Figma</span>
                    </div>
                    <div class="bg-white p-4 rounded-lg shadow-sm flex items-center">
                        <i class="fas fa-cloud text-3xl text-blue-400 mr-3"></i>
                        <span>AWS</span>
                    </div>
                    <div class="bg-white p-4 rounded-lg shadow-sm flex items-center">
                        <i class="fab fa-npm text-3xl text-red-600 mr-3"></i>
                        <span>npm</span>
                    </div>
                </div>
            </div>
        </div>
    </section>

    <!-- Portfolio Section -->
    <section id="portfolio" class="py-20 bg-gray-50">
        <div class="container mx-auto px-6">
            <h2 class="text-3xl font-bold text-center mb-4">Mon Portfolio</h2>
            <p class="text-gray-600 text-center max-w-2xl mx-auto mb-12">Découvrez une sélection de mes projets récents qui illustrent mon expertise et mon approche créative.</p>
            
            <div class="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-8">
                <!-- Project 1 -->
                <div class="project-card bg-white rounded-xl overflow-hidden shadow-md">
                    <div class="h-48 overflow-hidden">
                        <img src="e-commerce-3573828_1280-1280x640.webp" 
                             alt="Interface moderne d'un site e-commerce avec design épuré, listing de produits et panier d'achat" 
                             class="w-full h-full object-cover">
                    </div>
                    <div class="p-6">
                        <h3 class="text-xl font-semibold mb-2">Plateforme E-commerce</h3>
                        <p class="text-gray-600 mb-4">Site e-commerce complet avec panier, paiement et gestion administrative.</p>
                        <div class="flex flex-wrap gap-2 mb-4">
                            <span class="bg-indigo-100 text-indigo-800 text-xs px-3 py-1 rounded-full">React</span>
                            <span class="bg-indigo-100 text-indigo-800 text-xs px-3 py-1 rounded-full">Node.js</span>
                            <span class="bg-indigo-100 text-indigo-800 text-xs px-3 py-1 rounded-full">MongoDB</span>
                        </div>
                        <a href="#" class="text-indigo-600 font-semibold hover:underline">Voir le projet →</a>
                    </div>
                </div>
                
                <!-- Project 2 -->
                <div class="project-card bg-white rounded-xl overflow-hidden shadow-md">
                    <div class="h-48 overflow-hidden">
                        <img src="michlifen.jpg" 
                             alt="Interface dashboard analytique avec graphiques, diagrammes et composants de visualisation de données" 
                             class="w-full h-full object-cover">
                    </div>
                    <div class="p-6">
                        <h3 class="text-xl font-semibold mb-2">michlifen.com</h3>
                        <p class="text-gray-600 mb-4">Solution de visualisation de données en temps réel avec rapports personnalisables.</p>
                        <div class="flex flex-wrap gap-2 mb-4">
                            <span class="bg-purple-100 text-purple-800 text-xs px-3 py-1 rounded-full">Vue.js</span>
                            <span class="bg-purple-100 text-purple-800 text-xs px-3 py-1 rounded-full">Express</span>
                            <span class="bg-purple-100 text-purple-800 text-xs px-3 py-1 rounded-full">PostgreSQL</span>
                        </div>
                        <a href="https://www.michlifen.com/fr/restaurants-bars/restaurant-gastronomique.html" class="text-purple-600 font-semibold hover:underline">Voir le projet →</a>
                    </div>
                </div>
                
                <!-- Project 3 -->
                <div class="project-card bg-white rounded-xl overflow-hidden shadow-md">
                    <div class="h-48 overflow-hidden">
                        <img src="fitness-app-development-8.jpg" 
                             alt="Interface d'application mobile montrant le suivi fitness, métriques de santé et progression des entraînements" 
                             class="w-full h-full object-cover">
                    </div>
                    <div class="p-6">
                        <h3 class="text-xl font-semibold mb-2">Application Fitness</h3>
                        <p class="text-gray-600 mb-4">Application mobile de suivi d'activité physique avec plans d'entraînement personnalisés.</p>
                        <div class="flex flex-wrap gap-2 mb-4">
                            <span class="bg-green-100 text-green-800 text-xs px-3 py-1 rounded-full">React Native</span>
                            <span class="bg-green-100 text-green-800 text-xs px-3 py-1 rounded-full">Firebase</span>
                            <span class="bg-green-100 text-green-800 text-xs px-3 py-1 rounded-full">Redux</span>
                        </div>
                        <a href="#" class="text-green-600 font-semibold hover:underline">Voir le projet →</a>
                    </div>
                </div>
            </div>
            
            <div class="text-center mt-12">
                <a href="#" class="inline-flex items-center justify-center bg-indigo-600 text-white font-semibold py-3 px-6 rounded-lg shadow-lg hover:bg-indigo-700 transition-colors">
                    Voir tous mes projets
                    <i class="fas fa-arrow-right ml-2"></i>
                </a>
            </div>
        </div>
    </section>

    <!-- Experience Section -->
    <section id="experience" class="py-20 bg-white">
        <div class="container mx-auto px-6">
            <h2 class="text-3xl font-bold text-center mb-4">Mon Parcours Professionnel</h2>
            <p class="text-gray-600 text-center max-w-2xl mx-auto mb-12">Plus de 5 ans d'expérience dans le développement d'applications web et mobiles.</p>
            
            <div class="max-w-3xl mx-auto">
                <!-- Timeline Item 1 -->
                <div class="flex flex-col md:flex-row mb-12">
                    <div class="md:w-1/3 md:text-right mb-4 md:mb-0">
                        <h3 class="font-semibold">Développeur Fullstack Senior</h3>
                        <p class="text-indigo-600">TechSolutions Inc.</p>
                        <p class="text-gray-500">2021 - Présent</p>
                    </div>
                    <div class="md:w-2/3 md:pl-12">
                        <div class="bg-gray-50 p-6 rounded-lg">
                            <p>Développement et maintenance d'applications web complexes avec React, Node.js et MongoDB. Leadership d'une équipe de 4 développeurs et collaboration avec les designers UX/UI.</p>
                            <ul class="mt-4 list-disc list-inside space-y-2 text-gray-600">
                                <li>Augmentation de 40% des performances frontend</li>
                                <li>Implémentation de tests automatisés</li>
                                <li>Formation des nouveaux développeurs</li>
                            </ul>
                        </div>
                    </div>
                </div>
                
                <!-- Timeline Item 2 -->
                <div class="flex flex-col md:flex-row mb-12">
                    <div class="md:w-1/3 md:text-right mb-4 md:mb-0">
                        <h3 class="font-semibold">Développeur Frontend</h3>
                        <p class="text-purple-600">WebCraft Studio</p>
                        <p class="text-gray-500">2019 - 2021</p>
                    </div>
                    <div class="md:w-2/3 md:pl-12">
                        <div class="bg-gray-50 p-6 rounded-lg">
                            <p>Création d'interfaces utilisateur responsives et accessibles pour diverses applications web. Collaboration avec les designers pour transformer des maquettes en code fonctionnel.</p>
                            <ul class="mt-4 list-disc list-inside space-y-2 text-gray-600">
                                <li>Développement de 15+ sites web responsive</li>
                                <li>Optimisation SEO et performances</li>
                                <li>Intégration d'API RESTful</li>
                            </ul>
                        </div>
                    </div>
                </div>
                
                <!-- Timeline Item 3 -->
                <div class="flex flex-col md:flex-row">
                    <div class="md:w-1/3 md:text-right mb-4 md:mb-0">
                        <h3 class="font-semibold">Développeur Junior</h3>
                        <p class="text-blue-600">StartUp Innovante</p>
                        <p class="text-gray-500">2018 - 2019</p>
                    </div>
                    <div class="md:w-2/3 md:pl-12">
                        <div class="bg-gray-50 p-6 rounded-lg">
                            <p>Première expérience professionnelle dans le développement web. Participation au développement fullstack d'une application SaaS avec Python/Django et JavaScript.</p>
                            <ul class="mt-4 list-disc list-inside space-y-2 text-gray-600">
                                <li>Développement de features frontend et backend</li>
                                <li>Résolution de bugs et maintenance</li>
                                <li>Documentation technique</li>
                            </ul>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </section>

    <!-- Contact Section -->
    <section id="contact" class="py-20 bg-gray-50">
        <div class="container mx-auto px-6">
            <h2 class="text-3xl font-bold text-center mb-4">Contactez-moi</h2>
            <p class="text-gray-600 text-center max-w-2xl mx-auto mb-12">Disponible pour des projets freelance ou des opportunités en CDI. N'hésitez pas à me contacter!</p>
            
            <div class="grid grid-cols-1 md:grid-cols-2 gap-12">
                <div>
                    <h3 class="text-xl font-semibold mb-6">Informations de contact</h3>
                    <div class="space-y-4">
                        <div class="flex items-start">
                            <div class="bg-indigo-100 p-3 rounded-full mr-4">
                                <i class="fas fa-envelope text-indigo-600"></i>
                            </div>
                            <div>
                                <p class="font-semibold">Email</p>
                                <p class="text-gray-600">benismail722@gmail.com</p>
                            </div>
                        </div>
                        <div class="flex items-start">
                            <div class="bg-indigo-100 p-3 rounded-full mr-4">
                                <i class="fas fa-phone text-indigo-600"></i>
                            </div>
                            <div>
                                <p class="font-semibold">Téléphone</p>
                                <p class="text-gray-600">+212 6 79 56 57 47</p>
                            </div>
                        </div>
                        <div class="flex items-start">
                            <div class="bg-indigo-100 p-3 rounded-full mr-4">
                                <i class="fas fa-map-marker-alt text-indigo-600"></i>
                            </div>
                            <div>
                                <p class="font-semibold">Localisation</p>
                                <p class="text-gray-600">Rabat, Maroc</p>
                            </div>
                        </div>
                    </div>
                    
                    <div class="mt-8">
                        <h3 class="text-xl font-semibold mb-4">Réseaux sociaux</h3>
                        <div class="flex space-x-4">
                            <a href="https://www.linkedin.com/in/ismail-oujebbad-2ba1a82ab/" class="bg-indigo-600 text-white p-3 rounded-full hover:bg-indigo-700 transition-colors">
                                <i class="fab fa-linkedin-in"></i>
                            </a>
                            <a href="https://github.com/I6maeil" class="bg-indigo-600 text-white p-3 rounded-full hover:bg-indigo-700 transition-colors">
                                <i class="fab fa-github"></i>
                            </a>
                            <a href="#" class="bg-indigo-600 text-white p-3 rounded-full hover:bg-indigo-700 transition-colors">
                                <i class="fab fa-twitter"></i>
                            </a>
                            <a href="#" class="bg-indigo-600 text-white p-3 rounded-full hover:bg-indigo-700 transition-colors">
                                <i class="fab fa-dribbble"></i>
                            </a>
                        </div>
                    </div>
                </div>
                
                <div>
                    <form class="bg-white p-8 rounded-xl shadow-sm">
                        <!-- ... باقي الصفحة ... -->

<div>
  <form action="{{ url_for('contact') }}" method="POST" class="bg-white p-8 rounded-xl shadow-sm">
    <div class="mb-6">
      <label for="name" class="block text-gray-700 mb-2">Nom complet</label>
      <input name="name" type="text" id="name" required class="w-full px-4 py-3 border border-gray-300 rounded-lg focus:outline-none focus:ring-2 focus:ring-indigo-600">
    </div>
    <div class="mb-6">
      <label for="email" class="block text-gray-700 mb-2">Adresse email</label>
      <input name="email" type="email" id="email" required class="w-full px-4 py-3 border border-gray-300 rounded-lg focus:outline-none focus:ring-2 focus:ring-indigo-600">
    </div>
    <div class="mb-6">
      <label for="message" class="block text-gray-700 mb-2">Message</label>
      <textarea name="message" id="message" rows="5" required class="w-full px-4 py-3 border border-gray-300 rounded-lg focus:outline-none focus:ring-2 focus:ring-indigo-600"></textarea>
    </div>
    <button type="submit" class="w-full bg-indigo-600 text-white font-semibold py-3 px-6 rounded-lg shadow-lg hover:bg-indigo-700 transition-colors">
      Envoyer le message
    </button>
  </form>
</div>

<!-- ... باقي الصفحة ... -->

                        </button>
                    </form>
                </div>
            </div>
        </div>
    </section>
    <!-- Footer -->
    <footer class="bg-gray-800 text-white py-12">
        <div class="container mx-auto px-6">
            <div class="flex flex-col md:flex-row justify-between items-center">
                <div class="mb-6 md:mb-0">
                    <a href="#" class="text-2xl font-bold">Portfolio<span class="text-indigo-400">Pro</span></a>
                    <p class="mt-2 text-gray-400">WebDéveloppeur</p>
                </div>
                <div class="flex space-x-6">
                    <a href="#" class="text-gray-400 hover:text-white transition-colors">Mentions légales</a>
                    <a href="#" class="text-gray-400 hover:text-white transition-colors">Politique de confidentialité</a>
                </div>
            </div>
            <div class="border-t border-gray-700 mt-8 pt-8 text-center text-gray-400">
                <p>&copy; 2023 PortfolioPro. Tous droits réservés.</p>
            </div>
        </div>
    </footer>

    <script>
        // Mobile menu toggle
        document.getElementById('menu-toggle').addEventListener('click', function() {
            document.getElementById('mobile-menu').classList.add('menu-open');
        });
        
        document.getElementById('menu-close').addEventListener('click', function() {
            document.getElementById('mobile-menu').classList.remove('menu-open');
        });
        
        // Smooth scrolling for anchor links
        document.querySelectorAll('a[href^="#"]').forEach(anchor => {
            anchor.addEventListener('click', function (e) {
                e.preventDefault();
                
                // Close mobile menu if open
                document.getElementById('mobile-menu').classList.remove('menu-open');
                
                const targetId = this.getAttribute('href');
                if (targetId === '#') return;
                
                const targetElement = document.querySelector(targetId);
                if (targetElement) {
                    window.scrollTo({
                        top: targetElement.offsetTop - 80,
                        behavior: 'smooth'
                    });
                }
            });
        });
        
        // Animate skill bars on scroll
        function animateSkills() {
            const skillBars = document.querySelectorAll('.skill-bar');
            skillBars.forEach(bar => {
                const rect = bar.getBoundingClientRect();
                if (rect.top < window.innerHeight - 100) {
                    bar.style.width = bar.parentElement.previousElementSibling.lastChild.textContent;
                }
            });
        }
        
        window.addEventListener('scroll', animateSkills);
        window.addEventListener('load', animateSkills);
    </script>
</body>
</html>

├── static/
│     ├── style.css      ← تقدر تزيده لاحقاً
│     └── script.js      ← تقدر تزيده لاحقاً
