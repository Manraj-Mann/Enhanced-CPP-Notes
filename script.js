document.addEventListener('DOMContentLoaded', () => {
    generateTOC();
    updateHomeContent();
});

// Parse the README.md content to generate the table of contents and store chapter data
let chaptersData = new Map();
let activeSubchapter = null;

async function generateTOC() {
    try {
        const response = await fetch('README.md');
        const text = await response.text();
        const toc = document.getElementById('toc');
        
        // Clear existing content first
        toc.innerHTML = '';
        
        // Extract chapter sections with their file lists
        const chapters = text.match(/### \[Chapter.*?(?=### \[Chapter|$)/gs);
        
        // Keep track of added chapters to prevent duplicates
        const addedChapters = new Set();
        
        chapters.forEach(chapter => {
            const titleMatch = chapter.match(/### \[Chapter \d+ - (.*?)\]/);
            const emoji = chapter.match(/\) (.*?)\n/);
            
            if (titleMatch && emoji) {
                const title = titleMatch[1];
                
                // Skip if this chapter has already been added
                if (addedChapters.has(title)) {
                    return;
                }
                addedChapters.add(title);
                
                // Extract files list for this chapter
                const files = chapter.match(/- \[(.*?)\]\((.*?)\)/g);
                const filesData = files ? files.map(file => {
                    const [_, name, path] = file.match(/- \[(.*?)\]\((.*?)\)/);
                    return { 
                        name,
                        path: path.replace(/^[./]+/, ''),
                        encodedPath: encodePathComponents(path)
                    };
                }) : [];
                
                // Store chapter data
                chaptersData.set(title, filesData);
                
                // Create TOC link
                const link = document.createElement('a');
                link.href = '#';
                link.textContent = `${emoji[1]} ${title}`;
                link.onclick = (e) => {
                    e.preventDefault();
                    loadChapter(title);
                };
                toc.appendChild(link);
            }
        });
    } catch (error) {
        console.error('Error generating TOC:', error);
    }
}

// Helper function to properly encode path components
function encodePathComponents(path) {
    // Remove any leading ./ or / from the path
    const cleanPath = path.replace(/^[./]+/, '');
    
    // Split the path and encode each component
    return cleanPath.split('/')
        .map(component => 
            component.replace(/ /g, '%20') // Replace spaces with %20
                    .replace(/&/g, '%26')  // Handle special characters
                    .replace(/\?/g, '%3F')
                    .replace(/=/g, '%3D')
                    .replace(/\+/g, '%2B')
        )
        .join('/');
}

// Add this helper function for copying text
async function copyToClipboard(text) {
    try {
        await navigator.clipboard.writeText(text);
        return true;
    } catch (err) {
        console.error('Failed to copy text: ', err);
        return false;
    }
}

// Load chapter content
async function loadChapter(chapterTitle) {
    const contentDiv = document.getElementById('chapter-content');
    const files = chaptersData.get(chapterTitle);
    
    contentDiv.innerHTML = `
        <h2 class="chapter-title">${chapterTitle}</h2>
    `;
    
    if (!files || files.length === 0) {
        contentDiv.innerHTML += '<p>No files found for this chapter.</p>';
        return;
    }

    // Create chapter list
    const chapterList = document.createElement('div');
    chapterList.className = 'chapter-list';
    
    files.forEach(file => {
        // Create subchapter element
        const subchapter = document.createElement('div');
        subchapter.className = 'subchapter';
        subchapter.innerHTML = `
            <span>${file.name}</span>
        `;
        
        // Create code container (initially hidden)
        const codeContainer = document.createElement('div');
        codeContainer.className = 'code-container';
        
        subchapter.onclick = async () => {
            // Toggle active state
            if (activeSubchapter && activeSubchapter !== subchapter) {
                activeSubchapter.classList.remove('active');
                activeSubchapter.nextElementSibling.classList.remove('visible');
            }
            
            subchapter.classList.toggle('active');
            codeContainer.classList.toggle('visible');
            activeSubchapter = subchapter;

            // Load code if container is empty
            if (codeContainer.innerHTML === '') {
                const loadingSpinner = document.createElement('div');
                loadingSpinner.className = 'loading';
                codeContainer.appendChild(loadingSpinner);

                try {
                    const response = await fetch(file.encodedPath);
                    if (response.ok) {
                        const code = await response.text();
                        
                        // Create code header with filename and copy button
                        const codeHeader = document.createElement('div');
                        codeHeader.className = 'code-header';
                        
                        const fileName = document.createElement('span');
                        fileName.textContent = file.name;
                        
                        const copyButton = document.createElement('button');
                        copyButton.className = 'copy-button';
                        copyButton.textContent = 'Copy';
                        copyButton.onclick = async (e) => {
                            e.stopPropagation(); // Prevent triggering subchapter click
                            
                            if (await copyToClipboard(code)) {
                                copyButton.textContent = 'Copied!';
                                copyButton.classList.add('copied');
                                
                                // Reset button after 2 seconds
                                setTimeout(() => {
                                    copyButton.textContent = 'Copy';
                                    copyButton.classList.remove('copied');
                                }, 2000);
                            } else {
                                copyButton.textContent = 'Failed to copy';
                                setTimeout(() => {
                                    copyButton.textContent = 'Copy';
                                }, 2000);
                            }
                        };
                        
                        codeHeader.appendChild(fileName);
                        codeHeader.appendChild(copyButton);
                        
                        // Create code block
                        const codeBlock = document.createElement('div');
                        codeBlock.innerHTML = `
                            <pre><code class="language-cpp">${escapeHtml(code)}</code></pre>
                        `;
                        
                        // Clear loading spinner and add content
                        codeContainer.innerHTML = '';
                        codeContainer.appendChild(codeHeader);
                        codeContainer.appendChild(codeBlock);
                        
                        // Highlight code
                        Prism.highlightElement(codeContainer.querySelector('code'));
                    } else {
                        codeContainer.innerHTML = `
                            <p>Error: Could not load file content. (Status: ${response.status})</p>
                            <p>Attempted path: ${file.encodedPath}</p>
                        `;
                    }
                } catch (error) {
                    console.error(`Error loading file ${file.path}:`, error);
                    codeContainer.innerHTML = `
                        <p>Error: Could not load file content.</p>
                        <p class="error-details">${error.message}</p>
                        <p>Attempted path: ${file.encodedPath}</p>
                    `;
                }
            }
        };
        
        chapterList.appendChild(subchapter);
        chapterList.appendChild(codeContainer);
    });
    
    contentDiv.appendChild(chapterList);
}

// Helper function to escape HTML special characters
function escapeHtml(unsafe) {
    return unsafe
        .replace(/&/g, "&amp;")
        .replace(/</g, "&lt;")
        .replace(/>/g, "&gt;")
        .replace(/"/g, "&quot;")
        .replace(/'/g, "&#039;");
}

// Search functionality
document.getElementById('search').addEventListener('input', (e) => {
    const searchTerm = e.target.value.toLowerCase();
    const links = document.querySelectorAll('.toc a');
    
    links.forEach(link => {
        const text = link.textContent.toLowerCase();
        link.style.display = text.includes(searchTerm) ? 'block' : 'none';
    });
});

// Theme switcher
document.getElementById('theme-toggle').addEventListener('change', (e) => {
    document.documentElement.setAttribute('data-theme', e.target.checked ? 'dark' : 'light');
    // Save theme preference
    localStorage.setItem('theme', e.target.checked ? 'dark' : 'light');
});

// Initialize
document.addEventListener('DOMContentLoaded', () => {
    generateTOC();
    
    // Load saved theme preference
    const savedTheme = localStorage.getItem('theme');
    if (savedTheme) {
        document.documentElement.setAttribute('data-theme', savedTheme);
        document.getElementById('theme-toggle').checked = savedTheme === 'dark';
    } else if (window.matchMedia && window.matchMedia('(prefers-color-scheme: dark)').matches) {
        // Check system preference for dark mode
        document.getElementById('theme-toggle').checked = true;
        document.documentElement.setAttribute('data-theme', 'dark');
    }
});

// Add keyboard navigation
document.addEventListener('keydown', (e) => {
    if (e.key === '/' && e.target !== document.getElementById('search')) {
        e.preventDefault();
        document.getElementById('search').focus();
    }
});

// Add some CSS for error messages
const style = document.createElement('style');
style.textContent = `
    .error-details {
        color: #ff4444;
        font-size: 0.9em;
        margin-top: 0.5em;
    }
`;
document.head.appendChild(style);

// Add this function to fetch and parse the commit history
async function fetchRecentChanges() {
    try {
        const response = await fetch('https://api.github.com/repos/Manraj-Mann/Enhanced-CPP-Notes/commits?per_page=10');
        const commits = await response.json();
        return commits;
    } catch (error) {
        console.error('Error fetching commits:', error);
        return [];
    }
}

// Update the welcome message with recent changes
async function updateHomeContent() {
    const contentDiv = document.getElementById('chapter-content');
    
    contentDiv.innerHTML = `
        <div class="welcome-message">
            <h1 class="welcome-title">Enhanced C++ Notes 🚀</h1>
            <p class="welcome-subtitle">A comprehensive guide to modern C++ programming</p>
            
            <div class="recent-changes">
                <h2>Recent Updates</h2>
                <div class="changes-list" id="changes-list">
                    <div class="loading-spinner">Loading recent changes...</div>
                </div>
            </div>
        </div>
    `;

    try {
        const commits = await fetchRecentChanges();
        const changesList = document.getElementById('changes-list');
        
        if (commits.length === 0) {
            changesList.innerHTML = '<p class="no-changes">No recent changes found.</p>';
            return;
        }

        changesList.innerHTML = commits.map(commit => `
            <div class="change-item">
                <div class="change-header">
                    <span class="change-date">${new Date(commit.commit.author.date).toLocaleDateString()}</span>
                    <span class="change-author">${commit.commit.author.name}</span>
                </div>
                <p class="change-message">${commit.commit.message}</p>
                <a href="${commit.html_url}" target="_blank" class="change-link">View changes</a>
            </div>
        `).join('');

    } catch (error) {
        console.error('Error updating home content:', error);
        document.getElementById('changes-list').innerHTML = `
            <p class="error-message">Error loading recent changes. Please try again later.</p>
        `;
    }
} 